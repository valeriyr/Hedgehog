
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_collect_resource_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

#include "landscape_model/sources/actions/lm_iworkers_holder.hpp"

#include "landscape_model/ih/components/lm_iactions_component.hpp"
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
		Tools::Core::Object::Ptr playerComponent
			= _object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

		return	playerComponent
			&&	playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) == m_playerId
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
		Tools::Core::Object::Ptr resourceSource
			= _object.getMember< Tools::Core::Object::Ptr >( ResourceSourceComponent::Name );

		return	resourceSource
			&&	resourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ) == m_sourceOf;
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

	Tools::Core::Object::Ptr locateComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );
	Tools::Core::Object::Ptr playerComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );
	Tools::Core::Object::Ptr resourceHolderComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( ResourceHolderComponent::Name );

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
	{
		m_isInProcessing = false;
		return;
	}

	// Check objects

	Tools::Core::Object::Ptr targetLocateComponent
		= m_targetObject->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

	// Check distance

	if (	Geometry::getDistance(
					locateComponent->getMember< QPoint >( LocateComponent::Location )
				,	Geometry::getNearestPoint(
							locateComponent->getMember< QPoint >( LocateComponent::Location )
						,	LocateComponent::getRect( *targetLocateComponent ) ) )
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
		Tools::Core::Object::Ptr targetResourceSource
			= m_targetObject->getMember< Tools::Core::Object::Ptr >( ResourceSourceComponent::Name );
		Tools::Core::Object::Ptr targetLocation
			= m_targetObject->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

		if (	m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::UnderCollecting
			&&		targetResourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ResourceSourceComponent::ObjectInside )
				!=	m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
		{
			return;
		}

		if ( ResourceHolderComponent::isFull( *resourceHolderComponent, targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ) ) )
		{
			m_isInProcessing = ensureStorage();
			m_targetObject = m_resourceStarage;
		}

		if ( m_targetObject == m_resourceSource )
		{
			if ( targetResourceSource->getMember< qint32 >( ResourceSourceComponent::ResourceValue ) == 0 )
			{
				// TODO: find nearest source
				m_isInProcessing = false;
				return;
			}

			if ( !locateComponent->getMember< bool >( LocateComponent::IsHidden ) /* add checking should be hidden or not */ )
			{
				m_landscapeModel.getLandscape()->setEngaged(
						locateComponent->getMember< QPoint >( LocateComponent::Location )
					,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
					,	false );

				m_hiddenObject = m_landscapeModel.getLandscape()->hideObject( m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) );
				m_hiddenObject->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Collecting;

				m_workersHolder.addWorker( m_hiddenObject );

				targetResourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ResourceSourceComponent::ObjectInside )
					= m_hiddenObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey );

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::HolderHasStartedCollect::Type )
						.pushMember( Events::HolderHasStartedCollect::ObjectUniqueIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );

				m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::UnderCollecting;

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
						.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, m_resourceSource->getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, m_resourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectState, m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectDirection, targetLocation->getMember< Direction::Enum >( LocateComponent::Direction ) ) );
			}

			if ( !ResourceHolderComponent::isFull( *resourceHolderComponent, targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ) ) )
			{
				++m_collectingTicksCounter;

				const ResourceHolderComponent::StaticData::HoldResourceData& resourceData
					= resourceHolderComponent->getMember< ResourceHolderComponent::StaticData::HoldStaticData >( StaticDataTools::generateName( ResourceHolderComponent::StaticData::HoldStaticDataKey ) )
						.getData( targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ) );

				if ( m_collectingTicksCounter == resourceData.m_collectTime )
				{
					m_collectingTicksCounter = 0;

					int resourceSourceValue = targetResourceSource->getMember< qint32 >( ResourceSourceComponent::ResourceValue );

					if ( resourceSourceValue < resourceData.m_maxValue )
					{
						resourceHolderComponent->getMember< ResourcesData >( ResourceHolderComponent::HeldResources )
							.add( targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ), resourceSourceValue );
						resourceSourceValue = 0;
					}
					else
					{
						resourceHolderComponent->getMember< ResourcesData >( ResourceHolderComponent::HeldResources )
							.add( targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ), resourceData.m_maxValue );
						resourceSourceValue -= resourceData.m_maxValue;
					}

					targetResourceSource->getMember< qint32 >( ResourceSourceComponent::ResourceValue ) = resourceSourceValue;

					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ResourceSourceValueChanged::Type )
							.pushMember( Events::ResourceSourceValueChanged::ObjectUniqueIdAttribute, m_resourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ResourceSourceValueChanged::SourceResourceNameAttribute, targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ) )
							.pushMember( Events::ResourceSourceValueChanged::SourceResourceValueAttribute, targetResourceSource->getMember< qint32 >( ResourceSourceComponent::ResourceValue ) ) );

					holderResourcesCountCahnged = true;
				}
			}

			if ( ResourceHolderComponent::isFull( *resourceHolderComponent, targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) ) ) || !m_isInProcessing )
			{
				locateComponent->getMember< QPoint >( LocateComponent::Location )
					= m_landscapeModel.getLandscape()->getNearestLocation( *m_targetObject, m_object.getMember< QString >( ObjectNameKey ) );
				m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

				m_landscapeModel.getLandscape()->showObject( m_hiddenObject );

				m_workersHolder.removeWorker( m_hiddenObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) );

				targetResourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ResourceSourceComponent::ObjectInside ) = Tools::Core::Generators::IGenerator::ms_wrongId;

				m_hiddenObject.reset();

				m_landscapeModel.getLandscape()->setEngaged(
						locateComponent->getMember< QPoint >( LocateComponent::Location )
					,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
					,	true );

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::HolderHasStopCollect::Type )
						.pushMember( Events::HolderHasStopCollect::ObjectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::HolderHasStopCollect::ObjectLocationAttribute, locateComponent->getMember< QPoint >( LocateComponent::Location ) )
						.pushMember( Events::HolderHasStopCollect::ObjectUniqueIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::HolderHasStopCollect::ObjectEmplacementAttribute, locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) ) ) );

				m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
						.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, m_resourceSource->getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, m_resourceSource->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectState, m_resourceSource->getMember< ObjectState::Enum >( ObjectStateKey ) )
						.pushMember( Events::ObjectStateChanged::ObjectDirection, targetLocation->getMember< Direction::Enum >( LocateComponent::Direction ) ) );

				m_isInProcessing = ensureStorage();
				m_targetObject = m_resourceStarage;
			}
		}
	}
	else
	{
		boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );

		boost::intrusive_ptr< IResourceStorageComponent > targetResourceStorage
			= m_targetObject->getComponent< IResourceStorageComponent >( ComponentId::ResourceStorage );

		ResourcesData::ResourcesDataCollectionIterator
				begin = resourceHolderComponent->getMember< ResourcesData >( ResourceHolderComponent::HeldResources ).m_data.begin()
			,	end = resourceHolderComponent->getMember< ResourcesData >( ResourceHolderComponent::HeldResources ).m_data.end();

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
		Tools::Core::Object::Ptr playerComponent
			= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

		Tools::Core::Object::Ptr targetResourceSource
			= m_targetObject->getMember< Tools::Core::Object::Ptr >( ResourceSourceComponent::Name );

		StorageObjectsFilter filter(
				targetResourceSource->getMember< QString >( StaticDataTools::generateName( ResourceSourceComponent::StaticData::ResourceType ) )
			,	playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );
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
