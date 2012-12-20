
#ifndef __CON_PLUGIN_INSTANCE_HPP__
#define __CON_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/h/pm_base_plugin.hpp"
#include "plugins_manager/h/pm_interface_map.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace GUI
	{
		namespace WindowManager
		{
			 struct IWindowManager;
		}
	}

	namespace Core
	{
		namespace CommandsManager
		{
			struct ICommandsRegistry;
		}
	}
}

namespace Tools
{
	namespace Core
	{
		struct IMessenger;
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/

	struct IEnvironment;

	class MainView;

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

public:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		getWindowManager() const;

	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		getCommandsRegistry() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< MainView > m_consoleView;

	boost::intrusive_ptr< Tools::Core::IMessenger > m_consoleMessenger;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_PLUGIN_INSTANCE_HPP__
