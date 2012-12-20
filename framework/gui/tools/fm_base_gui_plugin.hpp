#ifndef __FM_BASE_GUI_PLUGIN_HPP__
#define __FM_BASE_GUI_PLUGIN_HPP__

#include "plugins_manager/h/pm_base_plugin.hpp"

#include "messenger/ms_imessenger.hpp"
#include "console/h/con_plugin_id.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {

/*---------------------------------------------------------------------------*/

class BasePlugin
	:	public Core::PluginsManager::BasePlugin
{

/*---------------------------------------------------------------------------*/

	typedef
		Core::PluginsManager::BasePlugin
		BaseType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BasePlugin()
		:	BaseType()
	{}

	virtual ~BasePlugin() {}

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Tools::Core::IMessenger >
	getConsoleMessenger() const
	{
		return
			getPluginInterface< Tools::Core::IMessenger >(
					Plugins::GUI::Console::PID_CONSOLE
				,	Tools::Core::IID_MESSENGER );
	}

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __FM_BASE_GUI_PLUGIN_HPP__
