
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/player/lm_player.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/sources/actions/lm_generate_resources_action.hpp"
#include "landscape_model/sources/actions/lm_move_action.hpp"
#include "landscape_model/sources/actions/lm_build_object_action.hpp"
#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/sources/notification_center/lm_inotification_center.hpp"

#include "landscape_model/sources/components/lm_builder_component.hpp"
#include "landscape_model/sources/components/lm_health_component.hpp"
#include "landscape_model/sources/components/lm_locate_component.hpp"
#include "landscape_model/sources/components/lm_selection_component.hpp"
#include "landscape_model/sources/components/lm_actions_component.hpp"
#include "landscape_model/sources/components/lm_move_component.hpp"
#include "landscape_model/sources/components/lm_generate_resources_component.hpp"
#include "landscape_model/sources/components/lm_attack_component.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"

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
	,	m_player()
	,	m_mutex( QMutex::Recursive )
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
	m_player.reset( new Player( m_environment, m_staticData ) );

	boost::intrusive_ptr< ILandscape >
		landscape( new Landscape( m_surfaceItemsCache, m_staticData, *this ) );

	try
	{
		m_landscapeSerializer.load( *landscape, _filePath );
	}
	catch( ... )
	{
		landscape.reset( new Landscape( m_surfaceItemsCache, m_staticData, *this ) );
		landscape->setSize( 20, 20 );
	}

	m_currentLandscape = landscape;

} // LandscapeModel::initCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::closeCurrentLandscape()
{
	m_currentLandscape.reset();
	m_player.reset();

} // LandscapeModel::closeCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveLandscape( const QString& _filePath ) const
{
	if ( m_currentLandscape )
		m_landscapeSerializer.save( *m_currentLandscape, _filePath );

} // LandscapeModel::saveLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeHandle >
LandscapeModel::getCurrentLandscape()
{
	return boost::intrusive_ptr< ILandscapeHandle >( new LandscapeHandle( m_currentLandscape, m_player, m_mutex ) );

} // LandscapeModel::getCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectObjects( const QRect& _rect )
{
	boost::intrusive_ptr< ILandscapeHandle > handle( getCurrentLandscape() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->selectObjects( _rect );

		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::selectObjects


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectObject( const Object::UniqueId& _id )
{
	boost::intrusive_ptr< ILandscapeHandle > handle( getCurrentLandscape() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->selectObject( _id );

		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::selectObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::moveSelectedObjects( const QPoint& _to )
{
	boost::intrusive_ptr< ILandscapeHandle > handle( getCurrentLandscape() );

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
							new MoveAction( m_environment, **begin, *handle->getLandscape(), m_pathFinder, _to ) ) );
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
		boost::intrusive_ptr< ILandscapeHandle > handle( getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			objectId = handle->getLandscape()->createObject( _location, _objectName );
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
	else
	{
		Framework::Core::EventManager::Event createObjectFailedEvent( Events::CreateObjectFailed::ms_type );
		createObjectFailedEvent.pushAttribute( Events::CreateObjectFailed::ms_objectNameAttribute, _objectName );
		createObjectFailedEvent.pushAttribute( Events::CreateObjectFailed::ms_objectLocationAttribute, _location );

		m_environment.riseEvent( createObjectFailedEvent );
	}

} // LandscapeModel::createObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setSurfaceItem(
		const QPoint& _location
	,	const Core::LandscapeModel::ISurfaceItem::Id& _id )
{
	boost::intrusive_ptr< ILandscapeHandle > handle( getCurrentLandscape() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->setSurfaceItem( _location, _id );

		Framework::Core::EventManager::Event surfaceItemChangedEvent( Events::SurfaceItemChanged::ms_type );
		surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemIdAttribute, _id );
		surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemLocationAttribute, _location );

		m_environment.riseEvent( surfaceItemChangedEvent );
	}

} // LandscapeModel::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeModel::buildObject( const Object::UniqueId& _parentObject, const QString& _objectName )
{
	boost::intrusive_ptr< ILandscapeHandle > handle( getCurrentLandscape() );

	if ( handle->getPlayer() )
	{
		boost::shared_ptr< Object > object = handle->getLandscape()->getObject( _parentObject );

		if ( object )
		{
			boost::intrusive_ptr< IBuilderComponent > builderComponent
				= object->getComponent< IBuilderComponent >( ComponentId::Builder );

			if ( builderComponent )
			{
				BuilderComponentStaticData::BuildObjectsDataCollectionIterator
					iterator =  builderComponent->getStaticData().m_buildObjects.find( _objectName );

				if (	iterator != builderComponent->getStaticData().m_buildObjects.end()
					&&	handle->getPlayer()->getResourcesData().hasEnaught( iterator->second->m_resourcesData ) )
				{
					handle->getPlayer()->getResourcesData().substruct( iterator->second->m_resourcesData );

					boost::intrusive_ptr< IActionsComponent > actionsComponent
						= object->getComponent< IActionsComponent >( ComponentId::Actions );

					if ( !actionsComponent->getAction( Actions::Build ) )
					{
						actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >(
							new BuildObjectAction( m_environment, *object, *handle->getPlayer(), *handle->getLandscape(), *this ) ) );
					}

					builderComponent->getBuildData().m_buildQueue.push_back( _objectName );

					Framework::Core::EventManager::Event builderQueueChangedEvent( Events::BuilderQueueChanged::ms_type );
					builderQueueChangedEvent.pushAttribute( Events::BuilderQueueChanged::ms_builderIdAttribute, object->getUniqueId() );
	
					m_environment.riseEvent( builderQueueChangedEvent );
				}
			}
		}
	}

} // LandscapeModel::buildObject


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
LandscapeModel::createObject( const QPoint& _location, const QString& _objectName ) const
{
	IStaticData::ObjectStaticData staticData = m_staticData.getObjectStaticData( _objectName );

	boost::shared_ptr< Object > object( new Object( _objectName ) );

	if ( staticData.m_healthData )
		object->addComponent(
				ComponentId::Health
			,	boost::intrusive_ptr< IComponent >( new HealthComponent( *object, *staticData.m_healthData ) ) );

	if ( staticData.m_locateData )
		object->addComponent(
				ComponentId::Locate
			,	boost::intrusive_ptr< IComponent >( new LocateComponent( *object, *staticData.m_locateData, _location ) ) );

	if ( staticData.m_selectionData )
		object->addComponent(
				ComponentId::Selection
			,	boost::intrusive_ptr< IComponent >( new SelectionComponent( *object, *staticData.m_selectionData ) ) );

	if ( staticData.m_builderData )
		object->addComponent(
				ComponentId::Builder
			,	boost::intrusive_ptr< IComponent >( new BuilderComponent( *object, *staticData.m_builderData ) ) );

	if ( staticData.m_actionsData )
		object->addComponent(
				ComponentId::Actions
			,	boost::intrusive_ptr< IComponent >( new ActionsComponent( *object, *staticData.m_actionsData ) ) );

	if ( staticData.m_moveData )
		object->addComponent(
				ComponentId::Move
			,	boost::intrusive_ptr< IComponent >( new MoveComponent( *object, *staticData.m_moveData ) ) );

	if ( staticData.m_attackData )
		object->addComponent(
				ComponentId::Attack
			,	boost::intrusive_ptr< IComponent >( new AttackComponent( *object, *staticData.m_attackData ) ) );

	if ( staticData.m_generateResourcesData )
	{
		object->addComponent(
				ComponentId::ResourcesGenerating
			,	boost::intrusive_ptr< IComponent >( new GenerateResourcesComponent( *object, *staticData.m_generateResourcesData ) ) );

		boost::intrusive_ptr< IActionsComponent > actionsComponent
			= object->getComponent< IActionsComponent >( ComponentId::Actions );
		actionsComponent->pushPeriodicalAction( boost::intrusive_ptr< IAction >( new GenerateResourcesAction( m_environment, *object, *m_player ) ) );
	}

	return object;

} // LandscapeModel::createObject


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
					// Periodical Actions loop

					if ( actionsComponent->hasPeriodicalActions() )
					{
						IActionsComponent::ActionsCollection periodicalActions;
						actionsComponent->fetchPeriodicalActions( periodicalActions );

						IActionsComponent::ActionsCollectionIterator
								beginPeriodicalActions = periodicalActions.begin()
							,	endPeriodicalActions = periodicalActions.end();

						for ( ; beginPeriodicalActions != endPeriodicalActions; ++beginPeriodicalActions )
						{
							( *beginPeriodicalActions )->processAction( Resources::TimeLimit );
						}
					}

					// Actions loop

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

	// Process notifications

	m_environment.getNotificationCenter()->processNotifiers();

	qint64 time = QDateTime::currentDateTime().toMSecsSinceEpoch() - startTime;

	if ( time > ( static_cast< float >( Resources::TimeLimit ) * 0.6f ) )
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
