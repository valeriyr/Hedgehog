
/** Plugin factory macroses */

#ifndef __CN_PLUGIN_FACTORY_HPP_
#define __CN_PLUGIN_FACTORY_HPP_

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugin.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

typedef
	Framework::Connector::IPlugin*
	(*PluginFactoryPtr) ();

/*---------------------------------------------------------------------------*/

const char* const PluginFactoryName = "getPlugin";

/*---------------------------------------------------------------------------*/

#define PLUGIN_FACTORY_DECLARATION( PLUGIN_INSTANCE )						\
																			\
extern "C" __declspec( dllexport )											\
Framework::Connector::IPlugin*												\
getPlugin()																	\
{																			\
	return new PLUGIN_INSTANCE();											\
}																			\

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGIN_FACTORY_HPP_
