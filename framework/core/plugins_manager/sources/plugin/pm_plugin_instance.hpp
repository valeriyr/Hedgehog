
#ifndef __PM_PLUGIN_INSTANCE_HPP__
#define __PM_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/sources/plugin/pm_iplugin_instance.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct IPluginsManagerInternal;

/*---------------------------------------------------------------------------*/

class PluginInstance
	:	public Tools::Core::BaseWrapper< IPluginInstance >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginInstance();

	virtual ~PluginInstance();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initialize( const std::string& _pluginsDirectory );

	/*virtual*/ void close();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IPluginsManagerInternal > m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_PLUGIN_INSTANCE_HPP__
