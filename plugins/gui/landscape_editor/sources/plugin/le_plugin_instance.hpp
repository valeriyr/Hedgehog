
#ifndef __LE_PLUGIN_INSTANCE_HPP__
#define __LE_PLUGIN_INSTANCE_HPP__

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
			 struct IDialogsManager;
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
			struct ILandscapeEditor;
			struct ILandscapeManager;
			struct ISurfaceItemsCache;
		}
	}

	namespace GUI
	{
		namespace MinimapViewer
		{
			struct IMinimapViewer;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IBaseView;
struct IEditorView;
struct ILandscapeEditorInternal;

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

	boost::intrusive_ptr< MinimapViewer::IMinimapViewer >
		getMinimapViewer() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeEditor >
		getLandscapeEditor() const;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItemsCache >
		getSurfaceItemsCache() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IBaseView > getObjectsView() const;

	boost::intrusive_ptr< IEditorView > getEditorView() const;

	boost::intrusive_ptr< IBaseView > getDescriptionView() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< ILandscapeEditorInternal > getGUILandscapeEditor() const;

/*---------------------------------------------------------------------------*/

	void fillSurfaceItemsCache();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< IBaseView > m_objectsView;

	boost::intrusive_ptr< IEditorView > m_editorView;

	boost::intrusive_ptr< IBaseView > m_descriptionView;

	boost::intrusive_ptr< ILandscapeEditorInternal > m_landscapeEditor;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_PLUGIN_INSTANCE_HPP__
