
#ifndef __MV_PLUGIN_INSTANCE_HPP__
#define __MV_PLUGIN_INSTANCE_HPP__

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
			 struct IWindowManager;
		}

		namespace ImagesManager
		{
			struct IImagesManager;
		}
	}
}

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ISurfaceItemsCache;
		}
	}

	namespace GUI
	{
		namespace LandscapeEditor
		{
			struct ILandscapeEditor;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IMinimapViewer;

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

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItemsCache >
		getSurfaceItemsCache() const;

	boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
		getImagesManager() const;

	boost::intrusive_ptr< LandscapeEditor::ILandscapeEditor >
		getLandscapeEditor() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IMinimapViewer > m_minimapViewer;

	boost::intrusive_ptr< IEnvironment > m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MV_PLUGIN_INSTANCE_HPP__
