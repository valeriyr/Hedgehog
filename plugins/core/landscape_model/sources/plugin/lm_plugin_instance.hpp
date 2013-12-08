
#ifndef __LM_PLUGIN_INSTANCE_HPP__
#define __LM_PLUGIN_INSTANCE_HPP__

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

		namespace EventManager
		{
			struct IEventManager;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeSerializer;
struct ILandscapeEditor;
struct ISurfaceItemsCache;
struct ILandscapeModel;
struct IObjectTypesCache;

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

	boost::intrusive_ptr< Framework::Core::EventManager::IEventManager >
		getEventManager() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IObjectTypesCache > m_objectTypesCache;

	boost::intrusive_ptr< ISurfaceItemsCache > m_surfaceItemsCache;

	boost::intrusive_ptr< ILandscapeSerializer > m_landscapeSerializer;

	boost::intrusive_ptr< ILandscapeEditor > m_landscapeEditor;

	boost::intrusive_ptr< ILandscapeModel > m_landscapeModel;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLUGIN_INSTANCE_HPP__
