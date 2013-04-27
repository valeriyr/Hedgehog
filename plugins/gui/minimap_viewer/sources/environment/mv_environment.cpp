
#include "minimap_viewer/sources/ph/mv_ph.hpp"

#include "minimap_viewer/sources/environment/mv_environment.hpp"

#include "minimap_viewer/sources/plugin/mv_plugin_instance.hpp"

#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_editor/ih/le_ilandscape_editor.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

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
Environment::changeVisibleAreaOnMainWindow(
		const float _relPosotionByX
	,	const float _relPosotionByY ) const
{
	m_pluginInstance.getLandscapeEditor()->setVisibilityRectPosition( _relPosotionByX, _relPosotionByY );

} // Environment::changeVisibleAreaOnMainWindow


/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
