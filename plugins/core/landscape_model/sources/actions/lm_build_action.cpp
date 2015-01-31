
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_build_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/ih/components/lm_ibuild_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iplayer_component.hpp"

#include "landscape_model/sources/actions/lm_iworkers_holder.hpp"
#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

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
	,	IWorkersHolder& _workersHolder
	,	GameObject& _object
	,	const QString& _objectName
	,	const QPoint& _atLocation
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_workersHolder( _workersHolder )
	,	m_objectName( _objectName )
	,	m_atRect( _atLocation, _environment.getStaticData()->getObjectStaticData( _objectName ).m_locateData->m_size )
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

	m_environment.riseEvent(
		Framework::Core::EventManager::Event( Events::BuildQueueChanged::Type )
			.pushMember( Events::BuildQueueChanged::BuilderIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );

	return true;

} // BuildAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
BuildAction::cancelProcessingInternal()
{
	boost::intrusive_ptr< IBuildComponent > buildComponent
		= m_object.getComponent< IBuildComponent >( ComponentId::Build );
	boost::intrusive_ptr< IPlayerComponent > playerComponent
		= m_object.getComponent< IPlayerComponent >( ComponentId::Player );

	if ( buildComponent->getBuildData().m_buildProgress != 0 )
	{
		boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getPlayerId() );

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

	m_environment.riseEvent(
		Framework::Core::EventManager::Event( Events::BuildQueueChanged::Type )
			.pushMember( Events::BuildQueueChanged::BuilderIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );

	return true;

} // BuildAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
BuildAction::processAction()
{
	// Common variables

	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IBuildComponent > buildComponent
		= m_object.getComponent< IBuildComponent >( ComponentId::Build );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );
	boost::intrusive_ptr< IPlayerComponent > playerComponent
		= m_object.getComponent< IPlayerComponent >( ComponentId::Player );

	IBuildComponent::Data& buildData = buildComponent->getBuildData();

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		// Check distance

		QPoint nearestPoint = Geometry::getNearestPoint( locateComponent->getLocation(), buildData.m_atRect );

		if ( Geometry::getDistance( locateComponent->getLocation(), nearestPoint ) > Geometry::ZeroDistance )
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

			if ( buildData.m_buildProgress == 0 )
			{
				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );

				boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getPlayerId() );

				bool newObjectCanBePlaced
					= m_landscapeModel.getLandscape()->canObjectBePlaced( buildData.m_atRect.topLeft(), buildData.m_objectName );

				IBuildComponent::StaticData::BuildDataCollectionIterator
					iterator = buildComponent->getStaticData().m_buildDatas.find( m_objectName );

				if (	!newObjectCanBePlaced
					||	!player
					||	iterator == buildComponent->getStaticData().m_buildDatas.end()
					||	!player->getResourcesData().isEnaught( iterator->second->m_resourcesData ) )
				{
					m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, true );
					m_isInProcessing = false;
					shouldBuildObject = false;
				}
				else
				{
					player->substructResources( iterator->second->m_resourcesData );

					startBuild( m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ), buildData.m_objectName, buildData.m_atRect.topLeft() );
				}
			}

			if ( shouldBuildObject )
			{
				++buildData.m_buildProgress;
				TickType totalTicks = buildComponent->getStaticData().m_buildDatas.find( buildData.m_objectName )->second->m_ticksCount;

				boost::shared_ptr< GameObject > targetObject
					= m_landscapeModel.getLandscape()->getObject( buildData.m_objectId );

				boost::shared_ptr< Tools::Core::Object > targetHealthComponent
					= targetObject->getMember< boost::shared_ptr< Tools::Core::Object > >( HealthComponent::Name );

				//targetHealthComponent->callVoidMethod< const qint32 >( HealthComponent::SetHealth, buildData.m_buildProgress * targetHealthComponent->getMember< qint32 >( StaticDataTools::generateName( HealthComponent::StaticData::MaxHealth ) ) / totalTicks );
				HealthComponent::setHealth( *targetHealthComponent, buildData.m_buildProgress * targetHealthComponent->getMember< qint32 >( StaticDataTools::generateName( HealthComponent::StaticData::MaxHealth ) ) / totalTicks );

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::ObjectHealthChanged::Type )
						.pushMember( Events::ObjectHealthChanged::ObjectNameAttribute, targetObject->getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::ObjectHealthChanged::ObjectIdAttribute, targetObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::ObjectHealthChanged::ObjectHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) ) );

				if ( buildData.m_buildProgress == totalTicks )
				{
					stopBuild( m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) );
					m_isInProcessing = false;
				}
			}

			m_environment.riseEvent(
				Framework::Core::EventManager::Event( Events::BuildQueueChanged::Type )
					.pushMember( Events::BuildQueueChanged::BuilderIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );
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
		const Tools::Core::Generators::IGenerator::IdType& _id
	,	const QString& _objectName
	,	const QPoint& _location )
{
	if ( m_landscapeModel.getLandscape() )
	{
		boost::shared_ptr< GameObject > object = m_landscapeModel.getLandscape()->hideObject( _id );

		if ( object )
		{
			object->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Building;

			m_workersHolder.addWorker( object );

			const Tools::Core::Generators::IGenerator::IdType objectId
				= m_landscapeModel.getLandscape()->createObjectForBuilding(
						_objectName
					,	_location
					,	object->getComponent< IPlayerComponent >( ComponentId::Player )->getPlayerId() );
			assert( objectId != Tools::Core::Generators::IGenerator::ms_wrongId );

			boost::intrusive_ptr< IBuildComponent > buildComponent
				= object->getComponent< IBuildComponent >( ComponentId::Build );
			boost::intrusive_ptr< ILocateComponent > locateComponent
				= object->getComponent< ILocateComponent >( ComponentId::Locate );

			buildComponent->getBuildData().m_objectId = objectId;

			m_environment.riseEvent(
				Framework::Core::EventManager::Event( Events::BuilderHasStartedBuild::Type )
					.pushMember( Events::BuilderHasStartedBuild::ObjectUniqueIdAttribute, _id ) );

			m_environment.riseEvent(
				Framework::Core::EventManager::Event( Events::ObjectStartBuilding::Type )
					.pushMember( Events::ObjectStartBuilding::ObjectNameAttribute, _objectName )
					.pushMember( Events::ObjectStartBuilding::ObjectLocationAttribute, _location )
					.pushMember( Events::ObjectStartBuilding::ObjectUniqueIdAttribute, objectId )
					.pushMember( Events::ObjectStartBuilding::ObjectEmplacementAttribute, locateComponent->getStaticData().m_emplacement ) );
		}
	}

} // BuildAction::startBuild


/*---------------------------------------------------------------------------*/


void
BuildAction::stopBuild( const Tools::Core::Generators::IGenerator::IdType& _id )
{
	if ( m_landscapeModel.getLandscape() )
	{
		boost::shared_ptr< GameObject > builder = m_workersHolder.getWorker( _id );
		assert( builder );

		boost::intrusive_ptr< ILocateComponent >
			locateComponent = builder->getComponent< ILocateComponent >( ComponentId::Locate );
		boost::intrusive_ptr< IBuildComponent >
			buildComponent = builder->getComponent< IBuildComponent >( ComponentId::Build );

		boost::shared_ptr< GameObject > targetObject
			= m_landscapeModel.getLandscape()->getObject( buildComponent->getBuildData().m_objectId );
		targetObject->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
				.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, targetObject->getMember< QString >( ObjectNameKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, targetObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectState, targetObject->getMember< ObjectState::Enum >( ObjectStateKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectDirection, targetObject->getComponent< ILocateComponent >( ComponentId::Locate )->getDirection() ) );

		locateComponent->setLocation(
			m_landscapeModel.getLandscape()->getNearestLocation(
					*targetObject
				,	builder->getMember< QString >( ObjectNameKey ) ) );
		builder->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

		m_landscapeModel.getLandscape()->showObject( builder );

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::BuilderHasFinishedBuild::Type )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectNameAttribute, builder->getMember< QString >( ObjectNameKey ) )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectLocationAttribute, locateComponent->getLocation() )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectUniqueIdAttribute, _id )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectEmplacementAttribute, locateComponent->getStaticData().m_emplacement ) );

		m_workersHolder.removeWorker( _id );
	}

} // BuildAction::stopBuild


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
