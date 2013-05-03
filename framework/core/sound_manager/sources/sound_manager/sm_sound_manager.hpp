
#ifndef __SM_SOUND_MANAGER_HPP__
#define __SM_SOUND_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "sound_manager/ih/sm_isound_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace SoundManager {

/*---------------------------------------------------------------------------*/

class SoundManager
	:	public Tools::Core::BaseWrapper< ISoundManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SoundManager( const QString& _resourcesDirectory );

	virtual ~SoundManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void play( const QString& _resourcePath );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QString m_resourcesDirectory;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SM_SOUND_MANAGER_HPP__
