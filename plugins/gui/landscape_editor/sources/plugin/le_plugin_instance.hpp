
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
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscapeEditorView;
struct ILandscapeEditorController;

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

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeEditor >
		getLandscapeEditor() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< ILandscapeEditorView > getObjectsView() const;

	boost::intrusive_ptr< ILandscapeEditorView > getEditorView() const;

	boost::intrusive_ptr< ILandscapeEditorView > getDescriptionView() const;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< ILandscapeEditorController > getLandscapeEditorController() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEnvironment > m_environment;

	boost::intrusive_ptr< ILandscapeEditorView > m_objectsView;

	boost::intrusive_ptr< ILandscapeEditorView > m_editorView;

	boost::intrusive_ptr< ILandscapeEditorView > m_descriptionView;

	boost::intrusive_ptr< ILandscapeEditorController > m_landscapeEditorController;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_PLUGIN_INSTANCE_HPP__
