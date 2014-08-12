
#ifndef __LV_PLUGIN_INSTANCE_HPP__
#define __LV_PLUGIN_INSTANCE_HPP__

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

		namespace AnimationManager
		{
			struct IAnimationManager;
			struct IAnimationsCache;
		}
	}

	namespace Core
	{
		namespace PluginsManager
		{
				struct ISystemInformation;
		}

		namespace CommandsManager
		{
			struct ICommandsRegistry;
		}

		namespace Settings
		{
			struct ISettings;
		}

		namespace EventManager
		{
			struct IEventManager;
		}

		namespace MultithreadingManager
		{
			struct IMultithreadingManager;
		}

		namespace SoundManager
		{
			struct ISoundManager;
		}

		namespace ScriptEngine
		{
			struct IExporter;
			struct IScriptsExecutor;
		}
	}
}

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct IModelLocker;
			struct ILandscapeEditor;
			struct ISurfaceItemsCache;
			struct IStaticData;
			struct IModelInformation;
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
struct IGraphicsInfoCache;

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

	boost::intrusive_ptr< Framework::Core::PluginsManager::ISystemInformation >
		getSystemInformation() const;

	boost::intrusive_ptr< Tools::Core::IMessenger >
		getSystemMessenger() const;

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		getWindowManager() const;

	boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
		getDialogsManager() const;

	boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
		getImagesManager() const;

	boost::intrusive_ptr< Framework::GUI::AnimationManager::IAnimationManager >
		getAnimationManager() const;

	boost::intrusive_ptr< Framework::GUI::AnimationManager::IAnimationsCache >
		getAnimationsCache() const;

	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		getCommandsManager() const;

	boost::intrusive_ptr< Framework::Core::Settings::ISettings >
		getSettings() const;

	boost::intrusive_ptr< Framework::Core::EventManager::IEventManager >
		getEventManager() const;

	boost::intrusive_ptr< Framework::Core::MultithreadingManager::IMultithreadingManager >
		getMultithreadingManager() const;

	boost::intrusive_ptr< Framework::Core::SoundManager::ISoundManager >
		getSoundManager() const;

	boost::intrusive_ptr< Framework::Core::ScriptEngine::IExporter >
		getScriptExporter() const;

	boost::intrusive_ptr< Framework::Core::ScriptEngine::IScriptsExecutor >
		getScriptsExecutor() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IModelLocker >
		getModelLocker() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItemsCache >
		getSurfaceItemsCache() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IStaticData >
		getStaticData() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IModelInformation >
		getModelInformation() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IGraphicsInfoCache > getGraphicsInfoCache() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void exportScriptAPI();

	void executeConfigurationScripts();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< ILandscapeViewer > m_landscapeViewer;

	boost::intrusive_ptr< ICommandsExecutor > m_commandsExecutor;

	boost::intrusive_ptr< IGraphicsInfoCache > m_graphicsInfoCache;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LV_PLUGIN_INSTANCE_HPP__
