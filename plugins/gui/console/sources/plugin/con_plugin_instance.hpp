
#ifndef __CON_PLUGIN_INSTANCE_HPP__
#define __CON_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/h/pm_base_plugin.hpp"
#include "plugins_manager/h/pm_interface_map.hpp"

#include "window_manager/ih/wm_iview.hpp"

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
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

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

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		getWindowManager() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	Framework::GUI::WindowManager::IView::Ptr m_consoleView;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_PLUGIN_INSTANCE_HPP__
