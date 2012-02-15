/** Common plugin interface */

#ifndef __CN_IPLUGIN_HPP__
#define __CN_IPLUGIN_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/h/cn_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPlugin
	:	public IBase
{
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGIN_HPP__
