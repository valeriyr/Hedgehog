
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
			struct ILandscapeEditor;
			struct ISurfaceItemsCache;
			struct IUnitsCache;
		}

		namespace GameManager
		{
			struct IGameManager;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscapeViewer;
struct ICommandsExecutor;

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

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		getWindowManager() const;

	boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
		getDialogsManager() const;

	boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
		getImagesManager() const;

	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		getCommandsManager() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeManager >
		getLandscapeManager() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeEditor >
		getLandscapeEditor() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItemsCache >
		getSurfaceItemsCache() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IUnitsCache >
		getUnitsCache() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Plugins::Core::GameManager::IGameManager >
		getGameManager() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void fillSurfaceItemsCache();

	void fillUnitsCache();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< ILandscapeViewer > m_landscapeViewer;

	boost::intrusive_ptr< ICommandsExecutor > m_commandsExecutor;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LV_PLUGIN_INSTANCE_HPP__
