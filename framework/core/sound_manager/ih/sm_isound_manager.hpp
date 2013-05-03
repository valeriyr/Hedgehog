
#ifndef __SM_ISOUND_MANAGER_HPP__
#define __SM_ISOUND_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace SoundManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_SOUND_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct ISoundManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void play( const QString& _resourcePath ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SM_ISOUND_MANAGER_HPP__
