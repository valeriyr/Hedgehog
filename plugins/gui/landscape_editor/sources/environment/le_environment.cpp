
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/environment/le_environment.hpp"

#include "landscape_editor/sources/plugin/le_plugin_instance.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_editor.hpp"

#include "landscape_editor/sources/views/le_ilandscape_editor_view.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


Environment::Environment( const PluginInstance& _pluginInstance )
	:	m_pluginInstance( _pluginInstance )
{
} // Environment::Environment


/*---------------------------------------------------------------------------*/


Environment::~Environment()
{
} // Environment::~Environment


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
Environment::getDialogsManager() const
{
	return m_pluginInstance.getDialogsManager();

} // Environment::getDialogsManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeEditor >
Environment::getLandscapeEditor() const
{
	return m_pluginInstance.getLandscapeEditor();

} // Environment::getLandscapeEditor


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorView >
Environment::getObjectsView() const
{
	return m_pluginInstance.getObjectsView();

} // Environment::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorView >
Environment::getEditorView() const
{
	return m_pluginInstance.getEditorView();

} // Environment::getEditorView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorView >
Environment::getDescriptionView() const
{
	return m_pluginInstance.getDescriptionView();

} // Environment::getDescriptionView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorView >
Environment::getMinimapView() const
{
	return m_pluginInstance.getMinimapView();

} // Environment::getMinimapView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorController >
Environment::getLandscapeEditorController() const
{
	return m_pluginInstance.getLandscapeEditorController();

} // Environment::getLandscapeEditorController


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
