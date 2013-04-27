
#include "minimap_viewer/sources/ph/mv_ph.hpp"

#include "minimap_viewer/sources/plugin/mv_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"
#include "images_manager/h/im_plugin_id.hpp"

#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"

#include "landscape_editor/ih/le_ilandscape_editor.hpp"
#include "landscape_editor/h/le_plugin_id.hpp"

#include "minimap_viewer/sources/environment/mv_environment.hpp"

#include "minimap_viewer/sources/minimap_view/mv_minimap_view.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_MINIMAP_VIEWER, m_minimapViewer.get() )

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
	m_environment.reset( new Environment( *this ) );

	m_minimapViewer.reset( new MinimapView( *m_environment ) );

	getWindowManager()->addView(
			m_minimapViewer
		,	Framework::GUI::WindowManager::ViewPosition::Right );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	getWindowManager()->removeView( m_minimapViewer );

	m_minimapViewer.reset();

	m_environment.reset();

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


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItemsCache >
PluginInstance::getSurfaceItemsCache() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::ISurfaceItemsCache >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_SURFACE_ITEMS_CACHE );

} // PluginInstance::getSurfaceItemsCache


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
PluginInstance::getImagesManager() const
{
	return
		getPluginInterface< Framework::GUI::ImagesManager::IImagesManager >(
				Framework::GUI::ImagesManager::PID_IMAGES_MANAGER
			,	Framework::GUI::ImagesManager::IID_IMAGES_MANAGER );

} // PluginInstance::getImageManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< LandscapeEditor::ILandscapeEditor >
PluginInstance::getLandscapeEditor() const
{
	return
		getPluginInterface< LandscapeEditor::ILandscapeEditor >(
				LandscapeEditor::PID_LANDSCAPE_EDITOR
			,	LandscapeEditor::IID_LANDSCAPE_EDITOR );

} // PluginInstance::getLandscapeEditor


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
