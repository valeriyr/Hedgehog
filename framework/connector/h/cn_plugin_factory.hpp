
/** Plugin factory macroses */

#ifndef __CN_PLUGIN_FACTORY_HPP_
#define __CN_PLUGIN_FACTORY_HPP_

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugin.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


const char* const PluginFactoryName = "createPlugin";


#define PLUGIN_FACTORY_DECLARATION()								\
																	\
__declspec( dllexport )												\
boost::intrusive_ptr< Framework::Connector::IPlugin >				\
createPlugin();														\

#define PLUGIN_FACTORY_DEFINITION()									\
																	\
boost::intrusive_ptr< Framework::Connector::IPlugin >				\
createPlugin()														\
{																	\
	return															\
		boost::intrusive_ptr< Framework::Connector::IPlugin >(		\
			new PluginInstance()									\
			);														\
}																	\

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGIN_FACTORY_HPP_
