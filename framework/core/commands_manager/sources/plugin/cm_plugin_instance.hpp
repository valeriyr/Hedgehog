
#ifndef __CM_PLUGIN_INSTANCE_HPP__
#define __CM_PLUGIN_INSTANCE_HPP__

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

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

struct ICommandsRegistry;
struct ICommandExecutor;

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

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< ICommandsRegistry > m_commandsRegistry;

	boost::intrusive_ptr< ICommandExecutor > m_commandExecutor;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_PLUGIN_INSTANCE_HPP__
