
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_collect_resource_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

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

	StorageObjectsFilter( const QString& _canStore )
		:	m_canStore( _canStore )
	{}

	/*virtual*/ bool check( const Object& _object ) const
	{
		boost::intrusive_ptr< IResourceStorageComponent > resourceStorage
			= _object.getComponent< IResourceStorageComponent >( ComponentId::ResourceStorage );

		return resourceStorage && resourceStorage->getStaticData().canBeStored( m_canStore );
	}

private:

	const QString m_canStore;
};

/*---------------------------------------------------------------------------*/

class SourceObjectsFilter
	:	public ILandscape::IObjectsFilter
{

public:

	SourceObjectsFilter( const QString& _sourceOf )
		:	m_sourceOf( _sourceOf )
	{}

	/*virtual*/ bool check( const Object& _object ) const
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
	,	Object& _object
	,	boost::shared_ptr< Object > _resourceSource
	)
	:	BaseAction( _environment, _landscapeModel, _object )
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
	,	boost::shared_ptr< Object > _resourceStorage
	,	Object& _object
	)
	:	BaseAction( _environment, _landscapeModel, _object )
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

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_isInProcessing = false;
		return;
	}

	// Check objects

	/*if ( !m_resourceSource )
	{
		// FIX
		SourceObjectsFilter filter( "Gold" );
		ILandscape::ObjectsCollection sourceObjects;

		m_landscapeModel.getLandscape()->fetchObjects( sourceObjects, filter );

		if ( sourceObjects.empty() )
		{
			m_isInProcessing = false;
			return;
		}

		m_resourceStarage = sourceObjects.front();
	}

	*/

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

		if ( m_resourceSource->getState() == ObjectState::UnderCollecting )
			return;

		if ( resourceHolderComponent->isFull( targetResourceSource->getStaticData().m_resource ) )
		{
			m_isInProcessing = ensureStorage();
			m_targetObject = m_resourceStarage;
		}

		if ( m_targetObject == m_resourceSource )
		{
			if ( !locateComponent->isHidden() /* add checking should be hidden or not */ )
			{
				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );

				m_hiddenObject = m_landscapeModel.getLandscape()->hideObject( m_object.getUniqueId() );
				m_hiddenObject->setState( ObjectState::Collecting );

				Framework::Core::EventManager::Event holderStartCollecting( Events::HolderHasStartedCollect::ms_type );
				holderStartCollecting.pushAttribute( Events::HolderHasStartedCollect::ms_objectUniqueIdAttribute, m_object.getUniqueId() );

				m_environment.riseEvent( holderStartCollecting );

				m_resourceSource->setState( ObjectState::UnderCollecting );

				Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_resourceSource->getName() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_resourceSource->getUniqueId() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_resourceSource->getState() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, targetLocation->getDirection() );

				m_environment.riseEvent( objectStateChangedEvent );
			}

			if ( !resourceHolderComponent->isFull( targetResourceSource->getStaticData().m_resource ) )
			{
				// FIX
				resourceHolderComponent->holdResources().add( targetResourceSource->getStaticData().m_resource, 10 );
				holderResourcesCountCahnged = true;

				if ( targetResourceSource->getResourceValue() == 0 )
				{
					m_isInProcessing = false;
				}
			}

			if ( resourceHolderComponent->isFull( targetResourceSource->getStaticData().m_resource ) || !m_isInProcessing )
			{
				locateComponent->setLocation( m_landscapeModel.getLandscape()->getNearestLocation( *m_targetObject, m_object.getName() ) );
				m_object.setState( ObjectState::Standing );

				m_landscapeModel.getLandscape()->showObject( m_hiddenObject );
				m_hiddenObject.reset();

				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, true );

				Framework::Core::EventManager::Event holderStopCollecting( Events::HolderHasStopCollect::ms_type );
				holderStopCollecting.pushAttribute( Events::HolderHasStopCollect::ms_objectNameAttribute, m_object.getName() );
				holderStopCollecting.pushAttribute( Events::HolderHasStopCollect::ms_objectLocationAttribute, locateComponent->getLocation() );
				holderStopCollecting.pushAttribute( Events::HolderHasStopCollect::ms_objectUniqueIdAttribute, m_object.getUniqueId() );
				holderStopCollecting.pushAttribute( Events::HolderHasStopCollect::ms_objectEmplacementAttribute, locateComponent->getStaticData().m_emplacement );

				m_environment.riseEvent( holderStopCollecting );

				m_resourceSource->setState( ObjectState::Standing );

				Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_resourceSource->getName() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_resourceSource->getUniqueId() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_resourceSource->getState() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, targetLocation->getDirection() );

				m_environment.riseEvent( objectStateChangedEvent );

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
		Framework::Core::EventManager::Event holderResourceCountChanged( Events::HolderResourceCountChanged::ms_type );
		holderResourceCountChanged.pushAttribute( Events::HolderResourceCountChanged::ms_objectUniqueIdAttribute, m_object.getUniqueId() );

		m_environment.riseEvent( holderResourceCountChanged );
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
		boost::intrusive_ptr< IResourceSourceComponent > targetResourceSource
			= m_targetObject->getComponent< IResourceSourceComponent >( ComponentId::ResourceSource );

		StorageObjectsFilter filter( targetResourceSource->getStaticData().m_resource );
		ILandscape::ObjectsCollection storageObjects;

		m_landscapeModel.getLandscape()->fetchObjects( storageObjects, filter );

		if ( storageObjects.empty() )
		{
			return false;
		}
		else
		{
			// FIX
			m_resourceStarage = storageObjects.front();
		}
	}

	return true;

} // CollectResourceAction::ensureStorage


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
