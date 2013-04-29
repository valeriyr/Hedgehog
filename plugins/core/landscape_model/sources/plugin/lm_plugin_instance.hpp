
#ifndef __LM_PLUGIN_INSTANCE_HPP__
#define __LM_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/h/pm_base_plugin.hpp"
#include "plugins_manager/h/pm_interface_map.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeSerializer;
struct ILandscapeEditor;
struct ILandscapeManager;
struct ISurfaceItemsCache;
struct IUnitsCache;

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

	boost::intrusive_ptr< ISurfaceItemsCache > m_surfaceItemsCache;

	boost::intrusive_ptr< IUnitsCache > m_unitsCache;

	boost::intrusive_ptr< ILandscapeSerializer > m_landscapeSerializer;

	boost::intrusive_ptr< ILandscapeEditor > m_landscapeEditor;

	boost::intrusive_ptr< ILandscapeManager > m_landscapeManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLUGIN_INSTANCE_HPP__
