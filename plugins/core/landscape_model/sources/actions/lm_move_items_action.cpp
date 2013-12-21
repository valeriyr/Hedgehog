
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_move_items_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_iunit.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "landscape_model/h/lm_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	boost::intrusive_ptr< IPathFinder > _pathFinder
	,	const QPoint& _to
	)
	:	BaseAction( _environment, _landscapeModel )
	,	m_pathFinder( _pathFinder )
	,	m_to( _to )
	,	m_movingData()
{
	boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

	if ( handle->getLandscape() )
	{
		ILandscape::UnitsCollection selectedUnits;
		handle->getLandscape()->fetchSelectedUnits( selectedUnits );

		ILandscape::UnitsCollectionIterator
				begin = selectedUnits.begin()
			,	end = selectedUnits.end();

		for ( ; begin != end; ++begin )
		{
			MovingData movingData;
			m_pathFinder->findPath( movingData.m_unitPath, *handle->getLandscape(), **begin, m_to );

			if ( !movingData.m_unitPath.empty() )
				m_movingData.insert( std::make_pair( ( *begin )->getUniqueId(), movingData ) );
		}
	}

} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::~MoveAction()
{
} // MoveAction::~MoveAction


/*---------------------------------------------------------------------------*/


void
MoveAction::processAction( const unsigned int _deltaTime )
{
	std::vector< Framework::Core::EventManager::Event > events;

	{
		boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			MovingDataCollectionIterator begin = m_movingData.begin();

			while ( begin != m_movingData.end() )
			{
				boost::intrusive_ptr< IUnit > unit = handle->getLandscape()->getUnit( begin->first );

				assert( begin->second.m_movingProgress < 1.0 );
				assert( !begin->second.m_unitPath.empty() );

				float movingDelta = ( static_cast< float >( _deltaTime ) / unit->getType()->getMovingSpeed() );
				begin->second.m_movingProgress += movingDelta;

				while ( begin->second.m_movingProgress >= 1.0 )
				{
					begin->second.m_movingProgress = begin->second.m_movingProgress - 1.0;
					unit->setPosition( QRect( begin->second.m_unitPath.front().x(), begin->second.m_unitPath.front().y(), 1, 1 ) );
					begin->second.m_unitPath.pop_front();

					if ( begin->second.m_unitPath.empty() )
						break;
				}

				if ( begin->second.m_unitPath.empty() )
				{
					MovingDataCollectionIterator temp = ++begin;
					--begin;
					m_movingData.erase( begin );
					begin = temp;
					continue;
				}

				Framework::Core::EventManager::Event unitMovedEvent( Events::UnitMoved::ms_type );
				unitMovedEvent.pushAttribute( Events::UnitMoved::ms_unitNameAttribute, unit->getType()->getName() );
				unitMovedEvent.pushAttribute( Events::UnitMoved::ms_unitIdAttribute, begin->first );
				unitMovedEvent.pushAttribute( Events::UnitMoved::ms_movingFromAttribute, QPoint( unit->getPosition().x(), unit->getPosition().y() ) );
				unitMovedEvent.pushAttribute( Events::UnitMoved::ms_movingToAttribute, begin->second.m_unitPath.front() );
				unitMovedEvent.pushAttribute( Events::UnitMoved::ms_movingProgressAttribute, begin->second.m_movingProgress );

				events.push_back( unitMovedEvent );

				++begin;
			}
		}
	}

	std::vector< Framework::Core::EventManager::Event >::const_iterator
			begin = events.begin()
		,	end = events.end();

	for ( ; begin != end; ++begin )
		m_environment.riseEvent( *begin );

} // MoveAction::processAction


/*---------------------------------------------------------------------------*/


void
MoveAction::unprocessAction( const unsigned int _deltaTime )
{
} // MoveAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
MoveAction::hasFinished() const
{
	return m_movingData.empty();

} // MoveAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
