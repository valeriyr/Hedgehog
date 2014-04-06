
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


CollectResourceAction::CollectResourceAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	boost::shared_ptr< Object > _resourceSource
	,	boost::shared_ptr< Object > _resourceStorage
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_hiddenObject()
	,	m_resourceSource( _resourceSource )
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

	bool goToSource = shoulGoToSource();

	if ( goToSource )
	{
		if ( !m_resourceSource )
		{
			// Find source
		}
	}
	else if ( !m_resourceStarage )
	{
		// FIX
		StorageObjectsFilter filter( "Gold" );
		ILandscape::ObjectsCollection storageObjects;

		m_landscapeModel.getLandscape()->fetchObjects( storageObjects, filter );

		if ( storageObjects.empty() )
		{
			m_isInProcessing = false;
			return;
		}

		m_resourceStarage = storageObjects.front();
	}

	boost::shared_ptr< Object > targetObject = goToSource ? m_resourceSource : m_resourceStarage;

	boost::intrusive_ptr< ILocateComponent > targetLocateComponent
		= targetObject->getComponent< ILocateComponent >( ComponentId::Locate );

	// Check distance

	if (	Geometry::getDistance(
					locateComponent->getLocation()
				,	Geometry::getNearestPoint(
							locateComponent->getLocation()
						,	targetLocateComponent->getRect() ) )
		>	Geometry::DiagonalDistance )
	{
		IPathFinder::PointsCollection path;
		JumpPointSearch::pathToObject( path, *m_landscapeModel.getLandscape(), m_object, *targetObject, Geometry::DiagonalDistance );

		if ( !path.empty() )
		{
			actionsComponent->pushFrontAction(
				boost::intrusive_ptr< IAction >(
					new MoveAction(
							m_environment
						,	m_landscapeModel
						,	m_object
						,	targetObject
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

	// FIX
	if ( !resourceHolderComponent->isFull( "Gold" ) )
	{
		boost::intrusive_ptr< IResourceSourceComponent > targetResourceSource
			= targetObject->getComponent< IResourceSourceComponent >( ComponentId::ResourceSource );

		if ( m_resourceSource->getState() == ObjectState::UnderCollecting )
			return;

		if ( !locateComponent->isHidden() /* add checking should be hidden or not */ )
		{
			m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );

			m_hiddenObject = m_landscapeModel.getLandscape()->hideObject( m_object.getUniqueId() );
			m_hiddenObject->setState( ObjectState::Collecting );

			Framework::Core::EventManager::Event holderStartCollecting( Events::HolderHasStartedCollect::ms_type );
			holderStartCollecting.pushAttribute( Events::HolderHasStartedCollect::ms_objectUniqueIdAttribute, m_object.getUniqueId() );

			m_environment.riseEvent( holderStartCollecting );
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
			locateComponent->setLocation(
				m_landscapeModel.getLandscape()->getNearestLocation(
						*targetObject
					,	m_object.getName() ) );
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
		}
	}
	else
	{
		boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getPlayerId() );

		boost::intrusive_ptr< IResourceStorageComponent > targetResourceStorage
			= targetObject->getComponent< IResourceStorageComponent >( ComponentId::ResourceStorage );

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
CollectResourceAction::shoulGoToSource() const
{
	boost::intrusive_ptr< IResourceHolderComponent > resourceHolderComponent
		= m_object.getComponent< IResourceHolderComponent >( ComponentId::ResourceHolder );

	return			m_resourceSource
				&&	!resourceHolderComponent->isFull(
						m_resourceSource->getComponent< IResourceSourceComponent >( ComponentId::ResourceSource )
							->getStaticData().m_resource );

} // CollectResourceAction::shoulGoToSource


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
