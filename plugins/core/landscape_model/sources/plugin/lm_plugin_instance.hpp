
#ifndef __LM_PLUGIN_INSTANCE_HPP__
#define __LM_PLUGIN_INSTANCE_HPP__

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

		namespace MultithreadingManager
		{
			struct IMultithreadingManager;
		}

		namespace EventManager
		{
			struct IEventManager;
		}

		namespace ScriptEngine
		{
			struct IExporter;
			struct IScriptsExecutor;
		}

		namespace NetworkManager
		{
			struct IConnectionManager;
		}

		namespace Settings
		{
				struct ISettings;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscapeSerializer;
struct IReplaySerializer;
struct ISurfaceItemsCache;
struct INotificationCenter;
struct IStaticData;
struct IModelLocker;
struct IModelInformation;

class LandscapeModel;

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

	boost::intrusive_ptr< Tools::Core::IMessenger > getSystemMessenger() const;

	boost::intrusive_ptr< Framework::Core::MultithreadingManager::IMultithreadingManager >
		getMultithreadingManager() const;

	boost::intrusive_ptr< Framework::Core::EventManager::IEventManager >
		getEventManager() const;

	boost::intrusive_ptr< Framework::Core::ScriptEngine::IExporter >
		getScriptExporter() const;

	boost::intrusive_ptr< Framework::Core::ScriptEngine::IScriptsExecutor >
		getScriptsExecutor() const;

	boost::intrusive_ptr< Framework::Core::NetworkManager::IConnectionManager >
		getConnectionManager() const;

	boost::intrusive_ptr< Framework::Core::Settings::ISettings >
		getSettings() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< INotificationCenter > getNotificationCenter() const;

	boost::intrusive_ptr< IStaticData > getStaticData() const;

	boost::intrusive_ptr< IModelInformation > getModelInformation() const;

	boost::intrusive_ptr< ISurfaceItemsCache > getSurfaceItemsCache() const;

	boost::intrusive_ptr< ILandscapeSerializer > getLandscapeSerializer() const;

	boost::intrusive_ptr< IReplaySerializer > getReplaySerializer() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IModelLocker > getLandscapeModelLocker();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void exportScriptAPI();

	void executeConfigurationScripts();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< IStaticData > m_staticData;

	boost::intrusive_ptr< IModelInformation > m_modelInformation;

	boost::intrusive_ptr< ISurfaceItemsCache > m_surfaceItemsCache;

	boost::intrusive_ptr< ILandscapeSerializer > m_landscapeSerializer;

	boost::intrusive_ptr< IReplaySerializer > m_replaySerializer;

	boost::intrusive_ptr< LandscapeModel > m_landscapeModel;

	boost::intrusive_ptr< INotificationCenter > m_notificationCenter;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLUGIN_INSTANCE_HPP__
