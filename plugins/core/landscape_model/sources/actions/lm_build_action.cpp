
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

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/geometry/lm_geometry.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuildAction::BuildAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	const QString& _objectName
	,	const QPoint& _atLocation
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_objectName( _objectName )
	,	m_atLocation( _atLocation )
	,	m_buildingFinished( false )
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
	buildComponent->getBuildData().m_atLocation = m_atLocation;

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
	m_buildingFinished = true;

	Framework::Core::EventManager::Event buildQueueChangedEvent( Events::BuildQueueChanged::ms_type );
	buildQueueChangedEvent.pushAttribute( Events::BuildQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );
	
	m_environment.riseEvent( buildQueueChangedEvent );

	return !m_moveAction || m_moveAction->cancelProcessing();

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

	IBuildComponent::Data& buildData = buildComponent->getBuildData();

	// Check if object is dying

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_buildingFinished = true;
	}
	else
	{
		// Check distance

		QPoint nearestPoint = Geometry::getNearestPoint( locateComponent->getLocation(), buildData.m_atLocation );

		if (	!m_moveAction
			&&	Geometry::getDistance( locateComponent->getLocation(), nearestPoint ) > 1.0f )
		{
			m_moveAction.reset(
				new MoveAction(
						m_environment
					,	m_landscapeModel
					,	m_object
					,	nearestPoint ) );

			m_moveAction->prepareToProcessing();
		}

		// Do action

		if ( m_moveAction )
		{
			m_moveAction->processAction( _deltaTime );

			if ( m_moveAction->hasFinished() )
				m_moveAction.reset();
		}
		else if ( !m_buildingFinished )
		{
			bool shouldBuildObject = true;

			if ( buildData.m_buildProgress == 0.0f )
			{
				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );

				boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( m_object.getPlayerId() );

				bool newObjectCanBePlaced
					= m_landscapeModel.getLandscape()->canObjectBePlaced( buildData.m_atLocation, buildData.m_objectName );

				IBuildComponent::StaticData::BuildDataCollectionIterator
					iterator = buildComponent->getStaticData().m_buildDatas.find( m_objectName );

				if (	!newObjectCanBePlaced
					||	!player
					||	iterator == buildComponent->getStaticData().m_buildDatas.end()
					||	!player->getResourcesData().hasEnaught( iterator->second->m_resourcesData ) )
				{
					m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, true );
					m_buildingFinished = true;
					shouldBuildObject = false;
				}
				else
				{
					player->substructResources( iterator->second->m_resourcesData );

					m_landscapeModel.startBuild( m_object.getUniqueId(), buildData.m_objectName, buildData.m_atLocation );
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
					m_landscapeModel.stopBuild( m_object.getUniqueId() );
					m_buildingFinished = true;
				}
			}

			Framework::Core::EventManager::Event buildQueueChangedEvent( Events::BuildQueueChanged::ms_type );
			buildQueueChangedEvent.pushAttribute( Events::BuildQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );
	
			m_environment.riseEvent( buildQueueChangedEvent );
		}
	}

	if ( m_buildingFinished )
	{
		buildData.reset();
	}

} // BuildAction::processAction


/*---------------------------------------------------------------------------*/


bool
BuildAction::hasFinished() const
{
	return ( !m_moveAction || m_moveAction->hasFinished() ) && m_buildingFinished;

} // BuildAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
BuildAction::getType() const
{
	return Actions::Build;

} // BuildAction::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
