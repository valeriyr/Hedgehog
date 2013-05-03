
#ifndef __GM_PLUGIN_INSTANCE_HPP__
#define __GM_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/h/pm_base_plugin.hpp"
#include "plugins_manager/h/pm_interface_map.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace Core
	{
		namespace MultithreadingManager
		{
			struct IMultithreadingManager;
		}

		namespace SoundManager
		{
			struct ISoundManager;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IGameManager;

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

	boost::intrusive_ptr< Framework::Core::MultithreadingManager::IMultithreadingManager >
		getMultithreadingManager() const;

	boost::intrusive_ptr< Framework::Core::SoundManager::ISoundManager >
		getSoundManager() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< IGameManager > m_gameManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_PLUGIN_INSTANCE_HPP__
