
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/plugin/le_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "landscape_editor/sources/editor_view/le_editor_view.hpp"
#include "landscape_editor/sources/objects_view/le_objects_view.hpp"
#include "landscape_editor/sources/description_view/le_description_view.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

END_INTERFACE_MAP()


/*---------------------------------------------------------------------------*/


PluginInstance::PluginInstance()
{
} // PluginInstance::PluginInstance


/*---------------------------------------------------------------------------*/


PluginInstance::~PluginInstance()
{
} // PluginInstance::~PluginInstance


/*---------------------------------------------------------------------------*/


void
PluginInstance::initialize()
{
	m_objectsView.reset( new ObjectsView() );
	m_editorView.reset( new EditorView() );
	m_descriptionView.reset( new DescriptionView() );

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		windowManager = getWindowManager();

	windowManager->addView(
			m_objectsView
		,	Framework::GUI::WindowManager::ViewPosition::Left );
	windowManager->addView(
			m_editorView
		,	Framework::GUI::WindowManager::ViewPosition::Center );
	windowManager->addView(
			m_descriptionView
		,	Framework::GUI::WindowManager::ViewPosition::Right );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		windowManager = getWindowManager();

	windowManager->removeView( m_descriptionView );
	windowManager->removeView( m_editorView );
	windowManager->removeView( m_objectsView );

	m_descriptionView.reset();
	m_editorView.reset();
	m_objectsView.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
PluginInstance::getWindowManager() const
{
	return
		getPluginInterface< Framework::GUI::WindowManager::IWindowManager >(
				Framework::GUI::WindowManager::PID_WINDOW_MANAGER
			,	Framework::GUI::WindowManager::IID_WINDOW_MANAGER );

} // PluginInstance::getWindowManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
