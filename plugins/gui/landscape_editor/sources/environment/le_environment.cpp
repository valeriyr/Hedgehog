
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/environment/le_environment.hpp"

#include "landscape_editor/sources/plugin/le_plugin_instance.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "landscape_editor/sources/views/le_ibase_view.hpp"
#include "landscape_editor/sources/views/le_ieditor_view.hpp"
#include "landscape_editor/sources/landscape_editor/le_ilandscape_editor_internal.hpp"

#include "minimap_viewer/ih/mv_iminimap_viewer.hpp"


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


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
Environment::getDefaultSurfaceItem() const
{
	return m_pluginInstance.getSurfaceItemsCache()->getDefaultSurfaceItem();

} // Environment::getDefaultSurfaceItem


/*---------------------------------------------------------------------------*/


const QPixmap&
Environment::getPixmap( const QString& _resourcePath, const QRect& _rect ) const
{
	return m_pluginInstance.getImagesManager()->getPixmap( _resourcePath, _rect );

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/


void
Environment::showLandscapeOnMinimap( const Plugins::Core::LandscapeModel::ILandscape& _landscape ) const
{
	return m_pluginInstance.getMinimapViewer()->showLandscape( _landscape );

} // Environment::showLandscapeOnMinimap


/*---------------------------------------------------------------------------*/


void
Environment::clearMinimap() const
{
	return m_pluginInstance.getMinimapViewer()->clear();

} // Environment::clearMinimap


/*---------------------------------------------------------------------------*/


void
Environment::setMinimapVisibilityRectSize(
		const float _relVisibleWidth
	,	const float _relVisibleHeight ) const
{
	return m_pluginInstance.getMinimapViewer()
		->setVisibilityRectSize( _relVisibleWidth, _relVisibleHeight );

} // Environment::setMinimapVisibilityRectSize


/*---------------------------------------------------------------------------*/


void
Environment::setMinimapVisibilityRectPosition(
		const float _relVisibleWidth
	,	const float _relVisibleHeight ) const
{
	return m_pluginInstance.getMinimapViewer()
		->setVisibilityRectPosition( _relVisibleWidth, _relVisibleHeight );

} // Environment::setMinimapVisibilityRectPosition


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBaseView >
Environment::getObjectsView() const
{
	return m_pluginInstance.getObjectsView();

} // Environment::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditorView >
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


boost::intrusive_ptr< ILandscapeEditorInternal >
Environment::getGUILandscapeEditor() const
{
	return m_pluginInstance.getGUILandscapeEditor();

} // Environment::getGUILandscapeEditor


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
