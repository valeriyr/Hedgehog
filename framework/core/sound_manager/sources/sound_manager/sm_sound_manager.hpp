
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

	 boost::shared_ptr< QSound > getSound( const QString& _resourcePath );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, boost::shared_ptr< QSound > >
		SoundsCache;
	typedef SoundsCache::iterator SoundsCacheIterator;

/*---------------------------------------------------------------------------*/

	const QString m_resourcesDirectory;

	SoundsCache m_soundsCache;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SM_SOUND_MANAGER_HPP__
