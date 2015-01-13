
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/player/lm_player.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"
#include "landscape_model/sources/ai/ai_manager/lm_iai_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {


/*---------------------------------------------------------------------------*/


Player::Player(
		const IEnvironment& _environment
	,	const Tools::Core::Generators::IGenerator::IdType _id
	,	const QString& _race
	,	const Tools::Core::Generators::IGenerator::IdType& _startPointId
	)
	:	m_environment( _environment )
	,	m_id( _id )
	,	m_startPointId( _startPointId )
	,	m_race( _race )
	,	m_name( Resources::DefaultPlayerName )
	,	m_aiName( m_environment.getAIManager()->getAIForRace( _race ) )
	,	m_type( PlayerType::Open )
	,	m_resourceData()
	,	m_notifier( *m_environment.getNotificationCenter(), this )
{
	setupResources();

} // Player::Player


/*---------------------------------------------------------------------------*/


Player::Player(
		const IEnvironment& _environment
	,	const Tools::Core::Generators::IGenerator::IdType _id
	,	const Tools::Core::Generators::IGenerator::IdType& _startPointId
	,	const PlayerType::Enum _type
	,	const QString& _race
	,	const QString& _name
	)
	:	m_environment( _environment )
	,	m_id( _id )
	,	m_startPointId( _startPointId )
	,	m_race( _race )
	,	m_name( _name )
	,	m_aiName( m_environment.getAIManager()->getAIForRace( _race ) )
	,	m_type( _type )
	,	m_resourceData()
	,	m_notifier( *m_environment.getNotificationCenter(), this )
	,	m_goals()
{
	setupResources();

} // Player::Player


/*---------------------------------------------------------------------------*/


Player::~Player()
{
} // Player::~Player


/*---------------------------------------------------------------------------*/


Tools::Core::Generators::IGenerator::IdType
Player::getUniqueId() const
{
	return m_id;

} // Player::getUniqueId


/*---------------------------------------------------------------------------*/


PlayerType::Enum
Player::getType() const
{
	return m_type;

} // Player::getType


/*---------------------------------------------------------------------------*/


const QString&
Player::getRace() const
{
	return m_race;

} // Player::getRace


/*---------------------------------------------------------------------------*/


const Tools::Core::Generators::IGenerator::IdType&
Player::getStartPointId() const
{
	return m_startPointId;

} // Player::getStartPointId


/*---------------------------------------------------------------------------*/


const QString&
Player::getName() const
{
	return m_name;

} // Player::getName


/*---------------------------------------------------------------------------*/


const QString&
Player::getAIName() const
{
	return m_aiName;

} // Player::getAIName


/*---------------------------------------------------------------------------*/


const ResourcesData&
Player::getResourcesData() const
{
	return m_resourceData;

} // Player::getResourcesData


/*---------------------------------------------------------------------------*/


void
Player::substructResources( const ResourcesData& _data )
{
	m_resourceData.substruct( _data );
	m_notifier.pushNotifyFunction( &Player::riseResourcesChanedEvent );

} // Player::substructResources


/*---------------------------------------------------------------------------*/


void
Player::addResources( const ResourcesData& _data )
{
	m_resourceData.add( _data );
	m_notifier.pushNotifyFunction( &Player::riseResourcesChanedEvent );

} // Player::addResources


/*---------------------------------------------------------------------------*/


void
Player::pushGoal( const Priority::Enum _priority, const IGoal::Ptr _goal )
{
	m_goals.insert( std::make_pair( _priority, _goal ) );

} // Player::pushGoal


/*---------------------------------------------------------------------------*/


void
Player::processGoals()
{
} // Player::processGoals


/*---------------------------------------------------------------------------*/


void
Player::addResources( const QString& _resourceName, const int _value )
{
	m_resourceData.add( _resourceName, _value );
	m_notifier.pushNotifyFunction( &Player::riseResourcesChanedEvent );

} // Player::addResources


/*---------------------------------------------------------------------------*/


void
Player::setName( const QString& _name )
{
	m_name = _name;

} // Player::setName


/*---------------------------------------------------------------------------*/


void
Player::setRace( const QString& _race )
{
	m_race = _race;
	m_aiName = m_environment.getAIManager()->getAIForRace( _race );

} // Player::setRace


/*---------------------------------------------------------------------------*/


void
Player::setType( const PlayerType::Enum _type )
{
	m_type = _type;

} // Player::setType


/*---------------------------------------------------------------------------*/


void
Player::riseResourcesChanedEvent()
{
	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ResourceValueChanged::Type ) );

} // Player::riseResourcesChanedEvent


/*---------------------------------------------------------------------------*/


void
Player::setupResources()
{
	IStaticData::ResourcesCollection resources;
	m_environment.getStaticData()->fetchResources( resources );

	IStaticData::ResourcesCollectionConstIterator
			begin = resources.begin()
		,	end = resources.end();

	for ( ; begin != end; ++begin )
		m_resourceData.pushResource( begin->first, begin->second );

} // Player::setupResources


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
