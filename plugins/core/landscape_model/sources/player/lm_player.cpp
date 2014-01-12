
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


Player::Player( const IEnvironment& _environment, const IStaticData& _staticData )
	:	m_environment( _environment )
	,	m_staticData( _staticData )
	,	m_id( ++IdGenerator )
	,	m_resourceData()
	,	m_notifier( *m_environment.getNotificationCenter(), this )
{
	IStaticData::ResourcesCollection resources;
	_staticData.fetchResources( resources );

	IStaticData::ResourcesCollectionConstIterator
			begin = resources.begin()
		,	end = resources.end();

	for ( ; begin != end; ++begin )
		m_resourceData.m_data.insert( std::make_pair( *begin, 0 ) );

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


IPlayer::ResourcesData&
Player::getResourcesData()
{
	return m_resourceData;

} // Player::getResourcesData


/*---------------------------------------------------------------------------*/


void
Player::incResource( const QString& _resourceName, const int _incTo )
{
	IPlayer::ResourcesData::ResourcesDataCollectionIterator iterator
		= m_resourceData.m_data.find( _resourceName );

	if ( iterator != m_resourceData.m_data.end() )
	{
		iterator->second += _incTo;
		m_notifier.pushNotifyFunction( &Player::riseResourcesChanedEvent );
	}

} // Player::incResource


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
