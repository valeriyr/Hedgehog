
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_scene/le_landscape_scene.hpp"

#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"
#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeScene::LandscapeScene(
		const ILandscapeEditorController& _landscapeEditorController
	,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
	,	QObject* _parent
	)
	:	QGraphicsScene( _parent )
	,	m_landscapeEditorController( _landscapeEditorController )
	,	m_imagesManager( _imagesManager )
{
} // LandscapeScene::LandscapeScene


/*---------------------------------------------------------------------------*/


LandscapeScene::~LandscapeScene()
{
} // LandscapeScene::~LandscapeScene


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasOpened()
{
	regenerate();

} // LandscapeScene::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeScene::setDefaultLandscape()
{
	regenerate();

} // LandscapeScene::setDefaultLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeScene::regenerate()
{
	clear();

	regenerateSurfaceLayer();
	regenerateObjectsLayer();

	setCorrectSceneSize();

} // LandscapeScene::regenerate


/*---------------------------------------------------------------------------*/


void
LandscapeScene::regenerateSurfaceLayer()
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape >
		landscape = m_landscapeEditorController.getEditableLandscape();

	if ( landscape )
	{
		for ( unsigned int i = 0; i < landscape->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < landscape->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > surfaceItem = landscape->getSurfaceItem( i, j );

				QGraphicsPixmapItem* item = addPixmap( m_imagesManager.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) );
				item->setOffset( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
			}
		}
	}

} // LandscapeScene::regenerateSurfaceLayer


/*---------------------------------------------------------------------------*/


void
LandscapeScene::regenerateObjectsLayer()
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape >
		landscape = m_landscapeEditorController.getEditableLandscape();

	if ( landscape )
	{
		addRect(
				QRect(
						3 * Resources::Landscape::CellSize
					,	3 * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize )
			,	QPen()
			,	QBrush( QColor( 111, 111, 111 ) ) );
	}

} // LandscapeScene::regenerateObjectsLayer


/*---------------------------------------------------------------------------*/


void
LandscapeScene::setCorrectSceneSize()
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape >
		landscape = m_landscapeEditorController.getEditableLandscape();

	if ( landscape )
	{
		setSceneRect( 0, 0, landscape->getWidth() * Resources::Landscape::CellSize, landscape->getHeight() * Resources::Landscape::CellSize );
	}
	else
	{
		setSceneRect( 0, 0, 0, 0 );
	}

} // LandscapeScene::setCorrectSceneSize


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
