/** Common plugin interface */

#ifndef __CN_IPLUGIN_HPP__
#define __CN_IPLUGIN_HPP__

/*---------------------------------------------------------------------------*/

#include "common_headers/ch_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPlugin
	:	public Common::IBase
{
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGIN_HPP__
