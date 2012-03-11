
/** Connector plugin manager interface */

#ifndef __CN_IPLUGINS_MANAGER_HPP__
#define __CN_IPLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

	const unsigned int PM_INTERFACE_ID = 1;

/*---------------------------------------------------------------------------*/

struct IPluginsManager
	:	public IBase
{
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGIN_MANAGER_HPP__
