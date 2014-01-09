
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"
#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/h/lm_events.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeModel::LandscapeModel(
		const IEnvironment& _environment
	,	const ILandscapeSerializer& _landscapeSerializer
	,	const ISurfaceItemsCache& _surfaceItemsCache
	,	const IStaticData& _staticData
	)
	:	m_environment( _environment )
	,	m_landscapeSerializer( _landscapeSerializer )
	,	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_staticData( _staticData )
	,	m_currentLandscape()
	,	m_landscapeLocker( QMutex::Recursive )
	,	m_pathFinder( new JumpPointSearch() )
{
	m_environment.startThread( Resources::ModelThreadName );
	m_actionsProcessingTaskHandle = m_environment.pushPeriodicalTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::gameMainLoop, this )
		,	Resources::TimeLimit );

} // LandscapeModel::LandscapeModel


/*---------------------------------------------------------------------------*/


LandscapeModel::~LandscapeModel()
{
	m_environment.removeTask( m_actionsProcessingTaskHandle );
	m_environment.stopThread( Resources::ModelThreadName );

} // LandscapeModel::~LandscapeModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initCurrentLandscape ( const QString& _filePath )
{
	boost::intrusive_ptr< IEditableLandscape >
		landscape( new Landscape( m_surfaceItemsCache, m_staticData ) );

	try
	{
		m_landscapeSerializer.load( *landscape, _filePath );
	}
	catch( ... )
	{
		landscape.reset( new Landscape( m_surfaceItemsCache, m_staticData ) );
		landscape->setSize( 20, 20 );
	}

	m_currentLandscape = landscape;

} // LandscapeModel::initCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::closeCurrentLandscape()
{
	m_currentLandscape.reset();

} // LandscapeModel::closeCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveLandscape( const QString& _filePath ) const
{
	if ( m_currentLandscape )
		m_landscapeSerializer.save( *m_currentLandscape, _filePath );

} // LandscapeModel::saveLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditableLandscape >
LandscapeModel::getCurrentLandscapeInternal() const
{
	return m_currentLandscape;

} // LandscapeModel::getCurrentLandscapeInternal


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeHandleInternal >
LandscapeModel::getCurrentEditableLandscape()
{
	return boost::intrusive_ptr< ILandscapeHandleInternal >( new LandscapeHandle( *this ) );

} // LandscapeModel::getCurrentEditableLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeHandle >
LandscapeModel::getCurrentLandscape()
{
	return getCurrentEditableLandscape();

} // LandscapeModel::getCurrentLandscape


/*---------------------------------------------------------------------------*/


QMutex&
LandscapeModel::getLandscapeLocker()
{
	return m_landscapeLocker;

} // LandscapeModel::getLandscapeLocker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectObjects( const QRect& _rect )
{
	{
		boost::intrusive_ptr< ILandscapeHandleInternal > handle( getCurrentEditableLandscape() );

		if ( handle->getLandscape() )
		{
			handle->getEditableLandscape()->selectObjects( _rect );
		}
	}

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );

} // LandscapeModel::selectObjects


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectObject( const Object::UniqueId& _id )
{
	{
		boost::intrusive_ptr< ILandscapeHandleInternal > handle( getCurrentEditableLandscape() );

		if ( handle->getLandscape() )
		{
			handle->getEditableLandscape()->selectObject( _id );
		}
	}

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );

} // LandscapeModel::selectObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::moveSelectedObjects( const QPoint& _to )
{
	{
		boost::intrusive_ptr< ILandscapeHandleInternal > handle( getCurrentEditableLandscape() );

		if ( handle->getLandscape() )
		{
			ILandscape::ObjectsCollection selectedObjects;
			handle->getLandscape()->fetchSelectedObjects( selectedObjects );

			ILandscape::ObjectsCollectionIterator
					begin = selectedObjects.begin()
				,	end = selectedObjects.end();

			for ( ; begin != end; ++begin )
			{
				boost::intrusive_ptr< IActionsComponent > actionsComponent
					= ( *begin )->getComponent< IActionsComponent >( ComponentId::Actions );

				if ( actionsComponent && actionsComponent->getStaticData().canDoAction( Actions::Move ) )
				{
					boost::intrusive_ptr< IAction > action = actionsComponent->getAction( Actions::Move );

					if ( action )
					{
						QVariant newPoint( _to );
						action->updateWithData( newPoint );
					}
					else
					{
						actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >(
								new MoveAction( m_environment, **begin, *handle->getEditableLandscape(), m_pathFinder, _to ) ) );
					}
				}
			}
		}
	}

} // LandscapeModel::moveSelectedObjects


/*---------------------------------------------------------------------------*/


void
LandscapeModel::createObject(
		const QPoint& _location
	,	const QString& _objectName )
{
	Object::UniqueId objectId = Object::ms_wrongId;

	{
		boost::intrusive_ptr< ILandscapeHandleInternal > handle( getCurrentEditableLandscape() );

		if ( handle->getLandscape() )
		{
			objectId = handle->getEditableLandscape()->createObject( _location, _objectName );
		}
	}

	if ( objectId != Object::ms_wrongId )
	{
		Framework::Core::EventManager::Event objectCreatedEvent( Events::ObjectCreated::ms_type );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectNameAttribute, _objectName );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectLocationAttribute, _location );
		objectCreatedEvent.pushAttribute( Events::ObjectCreated::ms_objectUniqueIdAttribute, objectId );

		m_environment.riseEvent( objectCreatedEvent );
	}

} // LandscapeModel::createObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setSurfaceItem(
		const QPoint& _location
	,	const Core::LandscapeModel::ISurfaceItem::Id& _id )
{
	{
		boost::intrusive_ptr< ILandscapeHandleInternal > handle( getCurrentEditableLandscape() );

		if ( handle->getLandscape() )
		{
			handle->getEditableLandscape()->setSurfaceItem( _location, _id );
		}
	}

	Framework::Core::EventManager::Event surfaceItemChangedEvent( Events::SurfaceItemChanged::ms_type );
	surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemIdAttribute, _id );
	surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemLocationAttribute, _location );

	m_environment.riseEvent( surfaceItemChangedEvent );

} // LandscapeModel::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeModel::gameMainLoop()
{
	qint64 startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

	{
		boost::intrusive_ptr< ILandscapeHandle > handle( getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			ILandscape::ObjectsCollection objects;
			handle->getLandscape()->fetchObjects( objects );

			ILandscape::ObjectsCollectionIterator
					begin = objects.begin()
				,	end = objects.end();

			for ( ; begin != end; ++begin )
			{
				boost::intrusive_ptr< IActionsComponent > actionsComponent
					= ( *begin )->getComponent< IActionsComponent >( ComponentId::Actions );

				if ( actionsComponent )
				{
					boost::intrusive_ptr< IAction > action = actionsComponent->frontAction();

					if ( action )
					{
						action->processAction( Resources::TimeLimit );

						if ( action->hasFinished() )
							actionsComponent->popFrontAction();
					}
				}
			}
		}
	}

	qint64 time = QDateTime::currentDateTime().toMSecsSinceEpoch() - startTime;

	if ( time > Resources::TimeLimit )
	{
		m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Warning
			,	QString( Resources::TimeLimitWarning ).arg( time ).arg( Resources::TimeLimit )  );
	}

} // LandscapeModel::gameMainLoop


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
