
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

	QSound::play( soundPath );

} // SoundManager::play


/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
