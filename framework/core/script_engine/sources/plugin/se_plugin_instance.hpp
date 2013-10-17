
#ifndef __SE_PLUGIN_INSTANCE_HPP__
#define __SE_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/h/pm_base_plugin.hpp"
#include "plugins_manager/h/pm_interface_map.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools
{
	namespace Core
	{
		struct IMessenger;
	}
}

namespace Framework
{
	namespace Core
	{
		namespace PluginsManager
		{
			struct ISystemInformation;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

struct IScriptsExecutor;
struct IEnvironment;

/*---------------------------------------------------------------------------*/

class PluginInstance
	:	public Framework::Core::PluginsManager::BasePlugin
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginInstance();

	virtual ~PluginInstance();

/*---------------------------------------------------------------------------*/

	INTERFACE_MAP_DECLARATION()

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initialize();

	/*virtual*/ void close();

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Tools::Core::IMessenger > getSystemMessenger() const;

	boost::intrusive_ptr< Core::PluginsManager::ISystemInformation >
		getSystemInformation() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IScriptsExecutor > m_scriptsExecutor;

	boost::intrusive_ptr< IEnvironment > m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_PLUGIN_INSTANCE_HPP__
