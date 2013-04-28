
#ifndef __LV_PLUGIN_INSTANCE_HPP__
#define __LV_PLUGIN_INSTANCE_HPP__

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
			struct IDialogsManager;
			struct IWindowManager;
		}

		namespace ImagesManager
		{
			struct IImagesManager;
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

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscapeManager;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IGameInitializer;

class LandscapeView;

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

	boost::intrusive_ptr< IGameInitializer > getGameInitializer() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		getWindowManager() const;

	boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
		getDialogsManager() const;

	boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
		getImagesManager() const;

	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		getCommandsManager() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeManager >
		getLandscapeManager() const;

/*---------------------------------------------------------------------------*/

	void showCurrentLandscapeModel();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< IGameInitializer > m_gameInitializer;

	boost::intrusive_ptr< LandscapeView > m_landscapeView;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LV_PLUGIN_INSTANCE_HPP__
