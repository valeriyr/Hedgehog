
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_collect_resource_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

#include "landscape_model/sources/actions/lm_iworkers_holder.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"
#include "landscape_model/ih/components/lm_iplayer_component.hpp"
#include "landscape_model/ih/components/lm_iresource_holder_component.hpp"
#include "landscape_model/ih/components/lm_iresource_source_component.hpp"
#include "landscape_model/ih/components/lm_iresource_storage_component.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class StorageObjectsFilter
	:	public ILandscape::IObjectsFilter
{

public:

	StorageObjectsFilter( const QString& _canStore, const Tools::Core::Generators::IGenerator::IdType& _playerId )
		:	m_canStore( _canStore )
		,	m_playerId( _playerId )
	{}

	/*virtual*/ bool check( const GameObject& _object ) const
	{
		boost::intrusive_ptr< IResourceStorageComponent > resourceStorage
			= _object.getComponent< IResourceStorageComponent >( ComponentId::ResourceStorage );
		boost::intrusive_ptr< IPlayerComponent > playerComponent
			= _object.getComponent< IPlayerComponent >( ComponentId::Player );

		return	playerComponent
			&&	playerComponent->getPlayerId() == m_playerId
			&&	resourceStorage
			&&	resourceStorage->getStaticData().canBeStored( m_canStore );
	}

private:

	const QString m_canStore;
	const Tools::Core::Generators::IGenerator::IdType m_playerId;
};

/*---------------------------------------------------------------------------*/

class SourceObjectsFilter
	:	public ILandscape::IObjectsFilter
{

public:

	SourceObjectsFilter( const QString& _sourceOf )
		:	m_sourceOf( _sourceOf )
	{}

	/*virtual*/ bool check( const GameObject& _object ) const
	{
		boost::intrusive_ptr< IResourceSourceComponent > resourceSource
			= _object.getComponent< IResourceSourceComponent >( ComponentId::ResourceSource );

		return resourceSource && resourceSource->getStaticData().m_resource == m_sourceOf;
	}

private:

	const QString m_sourceOf;
};

/*---------------------------------------------------------------------------*/


CollectResourceAction::CollectResourceAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	IWorkersHolder& _workersHolder
	,	GameObject& _object
	,	boost::shared_ptr< GameObject > _resourceSource
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_workersHolder( _workersHolder )
	,	m_hiddenObject()
	,	m_targetObject( _resourceSource )
	,	m_resourceSource( _resourceSource )
	,	m_resourceStarage()
	,	m_collectingTicksCounter( 0 )
{
} // CollectResourceAction::CollectResourceAction


/*---------------------------------------------------------------------------*/


CollectResourceAction::CollectResourceAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	IWorkersHolder& _workersHolder
	,	boost::shared_ptr< GameObject > _resourceStorage
	,	GameObject& _object
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_workersHolder( _workersHolder )
	,	m_hiddenObject()
	,	m_targetObject( _resourceStorage )
	,	m_resourceSource()
	,	m_resourceStarage( _resourceStorage )
	,	m_collectingTicksCounter( 0 )
{
} // CollectResourceAction::CollectResourceAction


/*---------------------------------------------------------------------------*/


CollectResourceAction::~CollectResourceAction()
{
} // CollectResourceAction::~CollectResourceAction


/*---------------------------------------------------------------------------*/


bool
CollectResourceAction::prepareToProcessingInternal()
{
	return true;

} // CollectResourceAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
CollectResourceAction::cancelProcessingInternal()
{
	return true;

} // CollectResourceAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
CollectResourceAction::processAction()
{
	// Common variables

	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );
	boost::intrusive_ptr< IPlayerComponent > playerComponent
		= m_object.getComponent< IPlayerComponent >( ComponentId::Player );
	boost::intrusive_ptr< IResourceHolderComponent > resourceHolderComponent
		= m_object.getComponent< IResourceHolderComponent >( ComponentId::ResourceHolder );

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
	{
		m_isInProcessing = false;
		return;
	}

	// Check objects

	boost::intrusive_ptr< ILocateComponent > targetLocateComponent
		= m_targetObject->getComponent< ILocateComponent >( ComponentId::Locate );

	// Check distance

	if (	Geometry::getDistance(
					locateComponent->getLocation()
				,	Geometry::getNearestPoint(
							locateComponent->getLocation()
						,	targetLocateComponent->getRect() ) )
		>	Geometry::DiagonalDistance )
	{
		IPathFinder::PointsCollection path;
		JumpPointSearch::pathToObject( path, *m_landscapeModel.getLandscape(), m_object, *m_targetObject, Geometry::DiagonalDistance );

		if ( !path.empty() )
		{
			actionsComponent->pushFrontAction(
				boost::intrusive_ptr< IAction >(
					new MoveAction(
							m_environment
						,	m_landscapeModel
						,	m_object
						,	m_targetObject
						,	path
						,	Geometry::DiagonalDistance ) ) );
			return;
		}
		else
		{
			m_isInProcessing = false;
			return;
		}
	}

	// Do action

	bool holderResourcesCountCahnged = false;

	if ( m_targetObject == m_resourceSource )
	{
		boost::intrusive_ptr< IResourceSourceComponent > targetResourceSource
			= m_targetObject->getComponent< IResourceSourceComponent >( ComponentId::ResourceSource );
		boost::intrusive_ptr< ILocateComponent > targetLocation
			= m_targetObject->getComponent< ILocateComponent >( ComponentId::Locate );

		if (	m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::UnderCollecting
			&&	targetResourceSource->getObjectInside() != m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
		{
			return;
		}

		if ( resourceHolderComponent->isFull( targetResourceSource->getStaticData().m_resource ) )
		{
			m_isInProcessing = ensureStorage();
			m_targetObject = m_resourceStarage;
		}

		if ( m_targetObject == m_resourceSource )
		{
			if ( targetResourceSource->getResourceValue() == 0 )
			{
				// TODO: find nearest source
				m_isInProcessing = false;
				return;
			}

			if ( !locateComponent->isHidden() /* add checking should be hidden or not */ )
			{
				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );

				m_hiddenObject = m_landscapeModel.getLandscape()->hideObject( m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) );
				m_hiddenObject->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Collecting;

				m_workersHolder.addWorker( m_hiddenObject );

				targetResourceSource->setObjectInside( m_hiddenObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) );

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::HolderHasStartedCollect::Type )
						.pushMember( Events::HolderHasStartedCollect::ObjectUniqueIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );

				m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::UnderCollecting;

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
						.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, m_resourceSource->getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, m_resourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectState, m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectDirection, targetLocation->getDirection() ) );
			}

			if ( !resourceHolderComponent->isFull( targetResourceSource->getStaticData().m_resource ) )
			{
				++m_collectingTicksCounter;

				const IResourceHolderComponent::StaticData::ResourceData& resourceData
					= resourceHolderComponent->getStaticData().getHoldData( targetResourceSource->getStaticData().m_resource );

				if ( m_collectingTicksCounter == resourceData.m_collectTime )
				{
					m_collectingTicksCounter = 0;

					int resourceSourceValue = targetResourceSource->getResourceValue();

					if ( resourceSourceValue < resourceData.m_maxValue )
					{
						resourceHolderComponent->holdResources().add( targetResourceSource->getStaticData().m_resource, resourceSourceValue );
						resourceSourceValue = 0;
					}
					else
					{
						resourceHolderComponent->holdResources().add( targetResourceSource->getStaticData().m_resource, resourceData.m_maxValue );
						resourceSourceValue -= resourceData.m_maxValue;
					}

					targetResourceSource->setResourceValue( resourceSourceValue );

					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ResourceSourceValueChanged::Type )
							.pushMember( Events::ResourceSourceValueChanged::ObjectUniqueIdAttribute, m_resourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ResourceSourceValueChanged::SourceResourceNameAttribute, targetResourceSource->getStaticData().m_resource )
							.pushMember( Events::ResourceSourceValueChanged::SourceResourceValueAttribute, targetResourceSource->getResourceValue() ) );

					holderResourcesCountCahnged = true;
				}
			}

			if ( resourceHolderComponent->isFull( targetResourceSource->getStaticData().m_resource ) || !m_isInProcessing )
			{
				locateComponent->setLocation( m_landscapeModel.getLandscape()->getNearestLocation( *m_targetObject, m_object.getMember< QString >( ObjectNameKey ) ) );
				m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

				m_landscapeModel.getLandscape()->showObject( m_hiddenObject );

				m_workersHolder.removeWorker( m_hiddenObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) );

				targetResourceSource->setObjectInside( Tools::Core::Generators::IGenerator::ms_wrongId );

				m_hiddenObject.reset();

				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, true );

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::HolderHasStopCollect::Type )
						.pushMember( Events::HolderHasStopCollect::ObjectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::HolderHasStopCollect::ObjectLocationAttribute, locateComponent->getLocation() )
						.pushMember( Events::HolderHasStopCollect::ObjectUniqueIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::HolderHasStopCollect::ObjectEmplacementAttribute, locateComponent->getStaticData().m_emplacement ) );

				m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
						.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, m_resourceSource->getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, m_resourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectState, m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectDirection, targetLocation->getDirection() ) );

				m_isInProcessing = ensureStorage();
				m_targetObject = m_resourceStarage;
			}
		}
	}
	else
	{
		boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getPlayerId() );

		boost::intrusive_ptr< IResourceStorageComponent > targetResourceStorage
			= m_targetObject->getComponent< IResourceStorageComponent >( ComponentId::ResourceStorage );

		ResourcesData::ResourcesDataCollectionIterator
				begin = resourceHolderComponent->holdResources().m_data.begin()
			,	end = resourceHolderComponent->holdResources().m_data.end();

		for ( ; begin != end; ++begin )
		{
			if ( targetResourceStorage->getStaticData().canBeStored( begin->first ) )
			{
				player->addResources( begin->first, begin->second );
				begin->second = 0;

				holderResourcesCountCahnged = true;
			}
		}

		// We shouldn't continue collectiong if resource source is not set
		if ( !m_resourceSource )
		{
			m_isInProcessing = false;
		}
		else
		{
			m_targetObject = m_resourceSource;
		}
	}

	if ( holderResourcesCountCahnged )
	{
		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::HolderResourceCountChanged::Type )
				.pushMember( Events::HolderResourceCountChanged::ObjectUniqueIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );
	}

} // CollectResourceAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
CollectResourceAction::getType() const
{
	return Actions::CollectResource;

} // CollectResourceAction::getType


/*---------------------------------------------------------------------------*/


bool
CollectResourceAction::ensureStorage()
{
	if ( !m_resourceStarage )
	{
		boost::intrusive_ptr< IPlayerComponent > playerComponent
			= m_object.getComponent< IPlayerComponent >( ComponentId::Player );

		boost::intrusive_ptr< IResourceSourceComponent > targetResourceSource
			= m_targetObject->getComponent< IResourceSourceComponent >( ComponentId::ResourceSource );

		StorageObjectsFilter filter( targetResourceSource->getStaticData().m_resource, playerComponent->getPlayerId() );
		ILandscape::ObjectsCollection storageObjects;

		m_landscapeModel.getLandscape()->fetchObjects( storageObjects, filter );

		if ( storageObjects.empty() )
		{
			return false;
		}
		else
		{
			m_resourceStarage = JumpPointSearch::nearestObject( *m_landscapeModel.getLandscape(), m_object, storageObjects, Geometry::DiagonalDistance );
		}
	}

	return true;

} // CollectResourceAction::ensureStorage


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
