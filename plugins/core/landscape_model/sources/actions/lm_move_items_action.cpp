
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_move_items_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

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
	/*Framework::Core::EventManager::Event unitMovedEvent( Events::UnitMoved::ms_type );
	unitMovedEvent.pushAttribute( Events::UnitMoved::, m_objectName );
	unitMovedEvent.pushAttribute( Events::UnitMoved::ms_objectPositionAttribute, m_position );
	unitMovedEvent.pushAttribute( Events::UnitMoved::ms_objectUniqueIdAttribute, unitId );

	m_environment.riseEvent( unitMovedEvent );*/

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
	return true;

} // MoveAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
