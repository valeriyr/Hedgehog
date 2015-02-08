
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_build_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

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
	,	m_atRect( _atLocation, _environment.getStaticData()->getObjectStaticData( _objectName ).m_locateData->getMember< QSize >( LocateComponent::StaticData::Size ) )
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
	Tools::Core::Object::Ptr buildComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( BuildComponent::Name );

	buildComponent->getMember< QString >( BuildComponent::ObjectName ) = m_objectName;
	buildComponent->getMember< QRect >( BuildComponent::AtRect ) = m_atRect;

	m_environment.riseEvent(
		Framework::Core::EventManager::Event( Events::BuildQueueChanged::Type )
			.pushMember( Events::BuildQueueChanged::BuilderIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );

	return true;

} // BuildAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
BuildAction::cancelProcessingInternal()
{
	Tools::Core::Object::Ptr buildComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( BuildComponent::Name );
	Tools::Core::Object::Ptr playerComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	if ( buildComponent->getMember< TickType >( BuildComponent::BuildProgress ) != 0 )
	{
		boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );

		if ( player )
		{
			BuildComponent::StaticData::Data::BuildDataCollectionIterator
				iterator = buildComponent->getMember< BuildComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( BuildComponent::StaticData::DataKey ) )
					->m_buildDatas.find( m_objectName );

			if ( iterator != buildComponent->getMember< BuildComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( BuildComponent::StaticData::DataKey ) )
					->m_buildDatas.end() )
			{
				player->addResources( iterator->second->m_resourcesData );
			}
		}
	}

	//buildComponent->callVoidMethod( BuildComponent::ClearData );
	BuildComponent::clearData( *buildComponent );

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

	Tools::Core::Object::Ptr locateComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );
	Tools::Core::Object::Ptr buildComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( BuildComponent::Name );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );
	Tools::Core::Object::Ptr playerComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		// Check distance

		QPoint nearestPoint = Geometry::getNearestPoint( locateComponent->getMember< QPoint >( LocateComponent::Location ), buildComponent->getMember< QRect  >( BuildComponent::AtRect ) );

		if ( Geometry::getDistance( locateComponent->getMember< QPoint >( LocateComponent::Location ), nearestPoint ) > Geometry::ZeroDistance )
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

			if ( buildComponent->getMember< TickType >( BuildComponent::BuildProgress ) == 0 )
			{
				m_landscapeModel.getLandscape()->setEngaged(
						locateComponent->getMember< QPoint >( LocateComponent::Location )
					,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
					,	false );

				boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );

				bool newObjectCanBePlaced
					= m_landscapeModel.getLandscape()->canObjectBePlaced( buildComponent->getMember< QRect >( BuildComponent::AtRect ).topLeft(), buildComponent->getMember< QString >( BuildComponent::ObjectName ) );

				BuildComponent::StaticData::Data::BuildDataCollectionIterator
					iterator = buildComponent->getMember< BuildComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( BuildComponent::StaticData::DataKey ) )
						->m_buildDatas.find( m_objectName );

				if (	!newObjectCanBePlaced
					||	!player
					||		iterator
						==	buildComponent->getMember< BuildComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( BuildComponent::StaticData::DataKey ) )
								->m_buildDatas.end()
					||	!player->getResourcesData().isEnaught( iterator->second->m_resourcesData ) )
				{
					m_landscapeModel.getLandscape()->setEngaged(
							locateComponent->getMember< QPoint >( LocateComponent::Location )
						,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
						,	true );
					m_isInProcessing = false;
					shouldBuildObject = false;
				}
				else
				{
					player->substructResources( iterator->second->m_resourcesData );

					startBuild( m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ), buildComponent->getMember< QString >( BuildComponent::ObjectName ), buildComponent->getMember< QRect >( BuildComponent::AtRect ).topLeft() );
				}
			}

			if ( shouldBuildObject )
			{
				++buildComponent->getMember< TickType >( BuildComponent::BuildProgress );
				TickType totalTicks = buildComponent->getMember< BuildComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( BuildComponent::StaticData::DataKey ) )
					->m_buildDatas.find( buildComponent->getMember< QString >( BuildComponent::ObjectName ) )->second->m_ticksCount;

				boost::shared_ptr< GameObject > targetObject
					= m_landscapeModel.getLandscape()->getObject( buildComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( BuildComponent::ObjectId ) );

				Tools::Core::Object::Ptr targetHealthComponent
					= targetObject->getMember< Tools::Core::Object::Ptr >( HealthComponent::Name );

				//targetHealthComponent->callVoidMethod< const qint32 >( HealthComponent::SetHealth, buildData.m_buildProgress * targetHealthComponent->getMember< qint32 >( StaticDataTools::generateName( HealthComponent::StaticData::MaxHealth ) ) / totalTicks );
				HealthComponent::setHealth( *targetHealthComponent, buildComponent->getMember< TickType >( BuildComponent::BuildProgress ) * targetHealthComponent->getMember< qint32 >( StaticDataTools::generateName( HealthComponent::StaticData::MaxHealth ) ) / totalTicks );

				m_environment.riseEvent(
					Framework::Core::EventManager::Event( Events::ObjectHealthChanged::Type )
						.pushMember( Events::ObjectHealthChanged::ObjectNameAttribute, targetObject->getMember< QString >( ObjectNameKey ) )
						.pushMember( Events::ObjectHealthChanged::ObjectIdAttribute, targetObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
						.pushMember( Events::ObjectHealthChanged::ObjectHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) ) );

				if ( buildComponent->getMember< TickType >( BuildComponent::BuildProgress ) == totalTicks )
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
		//buildComponent->callVoidMethod( BuildComponent::ClearData );
		BuildComponent::clearData( *buildComponent );
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
					,	object->getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name )->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );
			assert( objectId != Tools::Core::Generators::IGenerator::ms_wrongId );

			Tools::Core::Object::Ptr buildComponent
				= m_object.getMember< Tools::Core::Object::Ptr >( BuildComponent::Name );
			Tools::Core::Object::Ptr locateComponent
				= object->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

			buildComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( BuildComponent::ObjectId ) = objectId;

			m_environment.riseEvent(
				Framework::Core::EventManager::Event( Events::BuilderHasStartedBuild::Type )
					.pushMember( Events::BuilderHasStartedBuild::ObjectUniqueIdAttribute, _id ) );

			m_environment.riseEvent(
				Framework::Core::EventManager::Event( Events::ObjectStartBuilding::Type )
					.pushMember( Events::ObjectStartBuilding::ObjectNameAttribute, _objectName )
					.pushMember( Events::ObjectStartBuilding::ObjectLocationAttribute, _location )
					.pushMember( Events::ObjectStartBuilding::ObjectUniqueIdAttribute, objectId )
					.pushMember( Events::ObjectStartBuilding::ObjectEmplacementAttribute, locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) ) ) );
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

		Tools::Core::Object::Ptr
			locateComponent = builder->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );
		Tools::Core::Object::Ptr buildComponent
			= m_object.getMember< Tools::Core::Object::Ptr >( BuildComponent::Name );

		boost::shared_ptr< GameObject > targetObject
			= m_landscapeModel.getLandscape()->getObject( buildComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( BuildComponent::ObjectId ) );
		targetObject->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
				.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, targetObject->getMember< QString >( ObjectNameKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, targetObject->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectState, targetObject->getMember< ObjectState::Enum >( ObjectStateKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectDirection, targetObject->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name )->getMember< Direction::Enum >( LocateComponent::Direction ) ) );

		locateComponent->getMember< QPoint >( LocateComponent::Location )
			= m_landscapeModel.getLandscape()->getNearestLocation(
					*targetObject
				,	builder->getMember< QString >( ObjectNameKey ) );
		builder->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;

		m_landscapeModel.getLandscape()->showObject( builder );

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::BuilderHasFinishedBuild::Type )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectNameAttribute, builder->getMember< QString >( ObjectNameKey ) )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectLocationAttribute, locateComponent->getMember< QPoint >( LocateComponent::Location ) )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectUniqueIdAttribute, _id )
				.pushMember( Events::BuilderHasFinishedBuild::ObjectEmplacementAttribute, locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) ) ) );

		m_workersHolder.removeWorker( _id );
	}

} // BuildAction::stopBuild


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
