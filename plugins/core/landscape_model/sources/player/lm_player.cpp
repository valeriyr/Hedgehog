
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/player/lm_player.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static IPlayer::Id IdGenerator = 0;

/*---------------------------------------------------------------------------*/


Player::Player( const IStaticData& _staticData )
	:	m_staticData( _staticData )
	,	m_id( ++IdGenerator )
	,	m_resourceData()
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


const IPlayer::ResourcesData&
Player::getResourcesData() const
{
	return m_resourceData;

} // Player::getResourcesData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
