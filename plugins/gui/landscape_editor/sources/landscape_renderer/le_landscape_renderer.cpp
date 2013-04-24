
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_renderer/le_landscape_renderer.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeRenderer::LandscapeRenderer( Framework::GUI::ImagesManager::IImagesManager& _imagesManager )
	:	m_imagesManager( _imagesManager )
{
} // LandscapeRenderer::LandscapeRenderer


/*---------------------------------------------------------------------------*/


LandscapeRenderer::~LandscapeRenderer()
{
} // LandscapeRenderer::~LandscapeRenderer


/*---------------------------------------------------------------------------*/


void
LandscapeRenderer::renderSurface(
		const Core::LandscapeModel::ILandscape& _landscape
	,	QPixmap& _pixmap )
{
	QPainter painter;
	painter.begin( &_pixmap );
	painter.setRenderHint( QPainter::Antialiasing );

	for ( unsigned int i = 0; i < _landscape.getWidth() && i * Resources::Landscape::CellSize < _pixmap.width(); ++i )
	{
		for ( unsigned int j = 0; j < _landscape.getHeight() && j * Resources::Landscape::CellSize < _pixmap.height(); ++j )
		{
			boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > surfaceItem = _landscape.getSurfaceItem( i, j );

			painter.drawPixmap(
				QRect(
						i * Resources::Landscape::CellSize
					,	j * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize )
					,	m_imagesManager.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) );
		}
	}

} // LandscapeRenderer::renderSurface


/*---------------------------------------------------------------------------*/


void
LandscapeRenderer::renderObjects(
		const Core::LandscapeModel::ILandscape& _landscape
	,	QPixmap& _pixmap )
{
	_pixmap.fill( Qt::transparent );

	QPainter painter;
	painter.begin( &_pixmap );
	painter.setRenderHint( QPainter::Antialiasing );

	QBrush surfaceItemBrash( QColor( 111, 111, 111 ) );
	painter.fillRect(
			QRect(
					3 * Resources::Landscape::CellSize
				,	3 * Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize )
		, surfaceItemBrash );

} // LandscapeRenderer::renderObjects

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
