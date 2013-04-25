
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/environment/le_environment.hpp"

#include "landscape_editor/sources/plugin/le_plugin_instance.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "landscape_editor/sources/views/le_ibase_view.hpp"
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


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
Environment::getSurfaceItem( const unsigned int _index ) const
{
	return m_pluginInstance.getSurfaceItemsCache()->getSurfaceItem( _index );

} // Environment::getSurfaceItem


/*---------------------------------------------------------------------------*/


const QPixmap&
Environment::getPixmap( const QString& _resourcePath, const QRect& _rect ) const
{
	return m_pluginInstance.getImagesManager()->getPixmap( _resourcePath, _rect );

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBaseView >
Environment::getObjectsView() const
{
	return m_pluginInstance.getObjectsView();

} // Environment::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBaseView >
Environment::getEditorView() const
{
	return m_pluginInstance.getEditorView();

} // Environment::getEditorView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBaseView >
Environment::getDescriptionView() const
{
	return m_pluginInstance.getDescriptionView();

} // Environment::getDescriptionView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBaseView >
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
