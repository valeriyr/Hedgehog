
#include "sound_manager/sources/ph/sm_ph.hpp"

#include "sound_manager/sources/sound_manager/sm_sound_manager.hpp"

#include "sound_manager/sources/internal_resources/sm_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace SoundManager {

/*---------------------------------------------------------------------------*/


SoundManager::SoundManager( const QString& _resourcesDirectory )
	:	m_resourcesDirectory( _resourcesDirectory )
	,	m_soundsCache()
{
} // SoundManager::SoundManager


/*---------------------------------------------------------------------------*/


SoundManager::~SoundManager()
{
} // SoundManager::~SoundManager


/*---------------------------------------------------------------------------*/


void
SoundManager::play( const QString& _resourcePath )
{
	QString soundPath
		=	m_resourcesDirectory
		+	"/"
		+	Resources::SoundsDirecctory
		+	"/"
		+	_resourcePath
		+	Resources::SoundDefaultExtension;

	getSound( soundPath )->play();

} // SoundManager::play


/*---------------------------------------------------------------------------*/


boost::shared_ptr< QSound >
SoundManager::getSound( const QString& _resourcePath )
{
	SoundsCacheIterator iterator = m_soundsCache.find( _resourcePath );

	if ( iterator != m_soundsCache.end() )
		return iterator->second;

	boost::shared_ptr< QSound > sound( new QSound( _resourcePath ) );

	m_soundsCache.insert( std::make_pair( _resourcePath, sound ) );

	return sound;

} // SoundManager::getSound


/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
