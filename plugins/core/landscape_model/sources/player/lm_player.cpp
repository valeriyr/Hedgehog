
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/player/lm_player.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static IPlayer::Id IdGenerator = 0;

/*---------------------------------------------------------------------------*/


Player::Player(
		const IEnvironment& _environment
	,	const IStaticData& _staticData
	,	const QString& _race
	,	const StartPoint::Id& _startPointId
	)
	:	m_environment( _environment )
	,	m_staticData( _staticData )
	,	m_id( ++IdGenerator )
	,	m_startPointId( _startPointId )
	,	m_race( _race )
	,	m_name( "none" )
	,	m_type( PlayerType::Open )
	,	m_resourceData()
	,	m_notifier( *m_environment.getNotificationCenter(), this )
{
	IStaticData::ResourcesCollection resources;
	_staticData.fetchResources( resources );

	IStaticData::ResourcesCollectionConstIterator
			begin = resources.begin()
		,	end = resources.end();

	for ( ; begin != end; ++begin )
		m_resourceData.pushResource( *begin, 3000 );

} // Player::Player


/*---------------------------------------------------------------------------*/


Player::~Player()
{
} // Player::~Player


/*---------------------------------------------------------------------------*/


IPlayer::Id
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


const StartPoint::Id&
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
	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ResourceValueChanged::ms_type ) );

} // Player::riseResourcesChanedEvent


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
