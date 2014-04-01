
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_build_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/ih/components/lm_ibuild_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_ihealth_component.hpp"

#include "landscape_model/sources/actions/lm_ibuilders_holder.hpp"
#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/geometry/lm_geometry.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuildAction::BuildAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	IBuildersHolder& _buildersHolder
	,	const IStaticData& _staticData
	,	Object& _object
	,	const QString& _objectName
	,	const QPoint& _atLocation
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_buildersHolder( _buildersHolder )
	,	m_staticData( _staticData )
	,	m_objectName( _objectName )
	,	m_atRect( _atLocation, _staticData.getObjectStaticData( _objectName ).m_locateData->m_size )
{
} // BuildAction::BuildAction


/*---------------------------------------------------------------------------*/


BuildAction::~BuildAction()
{
} // BuildAction::~BuildAction


/*---------------------------------------------------------------------------*/


bool
BuildAction::prepareToProcessingInternal()
{
	boost::intrusive_ptr< IBuildComponent > buildComponent
		= m_object.getComponent< IBuildComponent >( ComponentId::Build );

	buildComponent->getBuildData().m_objectName = m_objectName;
	buildComponent->getBuildData().m_atRect = m_atRect;

	Framework::Core::EventManager::Event buildQueueChangedEvent( Events::BuildQueueChanged::ms_type );
	buildQueueChangedEvent.pushAttribute( Events::BuildQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );

	m_environment.riseEvent( buildQueueChangedEvent );

	return true;

} // BuildAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
BuildAction::cancelProcessingInternal()
{
	boost::intrusive_ptr< IBuildComponent > buildComponent
		= m_object.getComponent< IBuildComponent >( ComponentId::Build );

	if ( buildComponent->getBuildData().m_buildProgress != 0.0f )
	{
		boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( m_object.getPlayerId() );

		if ( player )
		{
			IBuildComponent::StaticData::BuildDataCollectionIterator
				iterator = buildComponent->getStaticData().m_buildDatas.find( m_objectName );

			if ( iterator != buildComponent->getStaticData().m_buildDatas.end() )
			{
				player->addResources( iterator->second->m_resourcesData );
			}
		}
	}

	buildComponent->getBuildData().reset();

	Framework::Core::EventManager::Event buildQueueChangedEvent( Events::BuildQueueChanged::ms_type );
	buildQueueChangedEvent.pushAttribute( Events::BuildQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );
	
	m_environment.riseEvent( buildQueueChangedEvent );

	return true;

} // BuildAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
BuildAction::processAction( const unsigned int _deltaTime )
{
	// Common variables

	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IBuildComponent > buildComponent
		= m_object.getComponent< IBuildComponent >( ComponentId::Build );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );

	IBuildComponent::Data& buildData = buildComponent->getBuildData();

	// Check if object is dying

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		// Check distance

		QPoint nearestPoint = Geometry::getNearestPoint( locateComponent->getLocation(), buildData.m_atRect );

		if ( Geometry::getDistance( locateComponent->getLocation(), nearestPoint ) > 0.0f )
		{
			IPathFinder::PointsCollection path;
			JumpPointSearch::pathToPoint( path, *m_landscapeModel.getLandscape(), m_object, nearestPoint );

			if ( !path.empty() )
			{
				actionsComponent->pushFrontAction(
					boost::intrusive_ptr< IAction >(
						new MoveAction(
								m_environment
							,	m_landscapeModel
							,	m_object
							,	nearestPoint
							,	path ) ) );
				return;
			}
			else
			{
				m_isInProcessing = false;
			}
		}

		// Do action

		if ( m_isInProcessing )
		{
			bool shouldBuildObject = true;

			if ( buildData.m_buildProgress == 0.0f )
			{
				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );

				boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( m_object.getPlayerId() );

				bool newObjectCanBePlaced
					= m_landscapeModel.getLandscape()->canObjectBePlaced( buildData.m_atRect.topLeft(), buildData.m_objectName );

				IBuildComponent::StaticData::BuildDataCollectionIterator
					iterator = buildComponent->getStaticData().m_buildDatas.find( m_objectName );

				if (	!newObjectCanBePlaced
					||	!player
					||	iterator == buildComponent->getStaticData().m_buildDatas.end()
					||	!player->getResourcesData().hasEnaught( iterator->second->m_resourcesData ) )
				{
					m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, true );
					m_isInProcessing = false;
					shouldBuildObject = false;
				}
				else
				{
					player->substructResources( iterator->second->m_resourcesData );

					startBuild( m_object.getUniqueId(), buildData.m_objectName, buildData.m_atRect.topLeft() );
				}
			}

			if ( shouldBuildObject )
			{
				int buildingTime = buildComponent->getStaticData().m_buildDatas.find( buildData.m_objectName )->second->m_buildTime;

				float buildingDelta = static_cast< float >( _deltaTime ) / buildingTime;

				buildData.m_buildProgress += buildingDelta;

				boost::shared_ptr< Object > targetObject
					= m_landscapeModel.getLandscape()->getObject( buildData.m_objectId );

				boost::intrusive_ptr< IHealthComponent > targetHealthComponent
					= targetObject->getComponent< IHealthComponent >( ComponentId::Health );

				targetHealthComponent->setHealth( buildData.m_buildProgress * targetHealthComponent->getStaticData().m_maximumHealth );

				Framework::Core::EventManager::Event objectDataChangedEvent( Events::ObjectDataChanged::ms_type );
				objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectNameAttribute, targetObject->getName() );
				objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectIdAttribute, targetObject->getUniqueId() );
				objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectHealth, targetHealthComponent->getHealth() );

				m_environment.riseEvent( objectDataChangedEvent );

				if ( buildData.m_buildProgress >= 1.0f )
				{
					stopBuild( m_object.getUniqueId() );
					m_isInProcessing = false;
				}
			}

			Framework::Core::EventManager::Event buildQueueChangedEvent( Events::BuildQueueChanged::ms_type );
			buildQueueChangedEvent.pushAttribute( Events::BuildQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );
	
			m_environment.riseEvent( buildQueueChangedEvent );
		}
	}

	if ( !m_isInProcessing )
	{
		buildData.reset();
	}

} // BuildAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
BuildAction::getType() const
{
	return Actions::Build;

} // BuildAction::getType


/*---------------------------------------------------------------------------*/


void
BuildAction::startBuild(
		const Object::Id& _id
	,	const QString& _objectName
	,	const QPoint& _location )
{
	if ( m_landscapeModel.getLandscape() )
	{
		boost::shared_ptr< Object > object = m_landscapeModel.getLandscape()->removeObject( _id );

		if ( object )
		{
			object->setState( ObjectState::Building );

			m_buildersHolder.addBuilder( object );

			const Object::Id objectId
				= m_landscapeModel.getLandscape()->createObjectForBuilding( _location, _objectName );
			assert( objectId != Object::ms_wrongId );

			boost::intrusive_ptr< IBuildComponent > buildComponent
				= object->getComponent< IBuildComponent >( ComponentId::Build );
			boost::intrusive_ptr< ILocateComponent > locateComponent
				= object->getComponent< ILocateComponent >( ComponentId::Locate );

			buildComponent->getBuildData().m_objectId = objectId;

			Framework::Core::EventManager::Event objectRemovedEvent( Events::ObjectRemoved::ms_type );
			objectRemovedEvent.pushAttribute( Events::ObjectRemoved::ms_objectUniqueIdAttribute, _id );

			m_environment.riseEvent( objectRemovedEvent );

			Framework::Core::EventManager::Event objectStartBuildingEvent( Events::ObjectStartBuilding::ms_type );
			objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectNameAttribute, _objectName );
			objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectLocationAttribute, _location );
			objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectUniqueIdAttribute, objectId );
			objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectEmplacementAttribute, locateComponent->getStaticData().m_emplacement );

			m_environment.riseEvent( objectStartBuildingEvent );
		}
	}

} // BuildAction::startBuild


/*---------------------------------------------------------------------------*/


void
BuildAction::stopBuild( const Object::Id& _id )
{
	if ( m_landscapeModel.getLandscape() )
	{
		boost::shared_ptr< Object > builder = m_buildersHolder.getBuilder( _id );
		assert( builder );

		boost::intrusive_ptr< ILocateComponent >
			locateComponent = builder->getComponent< ILocateComponent >( ComponentId::Locate );
		boost::intrusive_ptr< IBuildComponent >
			buildComponent = builder->getComponent< IBuildComponent >( ComponentId::Build );

		boost::shared_ptr< Object > targetObject
			= m_landscapeModel.getLandscape()->getObject( buildComponent->getBuildData().m_objectId );
		targetObject->setState( ObjectState::Standing );

		Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, targetObject->getName() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, targetObject->getUniqueId() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, targetObject->getState() );
		objectStateChangedEvent.pushAttribute(
				Events::ObjectStateChanged::ms_objectDirection
			,	targetObject->getComponent< ILocateComponent >( ComponentId::Locate )->getDirection() );

		m_environment.riseEvent( objectStateChangedEvent );

		locateComponent->setLocation(
			m_landscapeModel.getLandscape()->getNearestLocation(
					*targetObject
				,	builder->getName() ) );
		builder->setState( ObjectState::Standing );

		m_landscapeModel.getLandscape()->addObject( builder );

		Framework::Core::EventManager::Event builderHasFinishedBuildEvent( Events::BuilderHasFinishedBuild::ms_type );
		builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectNameAttribute, builder->getName() );
		builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectLocationAttribute, locateComponent->getLocation() );
		builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectUniqueIdAttribute, _id );
		builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectEmplacementAttribute, locateComponent->getStaticData().m_emplacement );

		m_environment.riseEvent( builderHasFinishedBuildEvent );

		m_buildersHolder.removeBuilder( _id );
	}

} // BuildAction::stopBuild


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
