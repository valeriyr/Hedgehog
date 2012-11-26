
#ifndef __WM_PLUGIN_INSTANCE_HPP__
#define __WM_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/h/pm_base_plugin.hpp"
#include "plugins_manager/h/pm_interface_map.hpp"

/*---------------------------------------------------------------------------*/

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
namespace GUI {
namespace WindowManager {

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

	boost::intrusive_ptr< Core::PluginsManager::ISystemInformation >
		getSystemInformation() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< QMainWindow > m_mainWindow;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_PLUGIN_INSTANCE_HPP__
