
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/landscape_scene/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

// #include "lv_landscape_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeScene::LandscapeScene( const IEnvironment& _environment, QObject* _parent )
	:	QGraphicsScene( _parent )
	,	m_environment( _environment )
{
} // LandscapeScene::LandscapeScene


/*---------------------------------------------------------------------------*/


LandscapeScene::~LandscapeScene()
{
} // LandscapeScene::~LandscapeScene


/*---------------------------------------------------------------------------*/


void
LandscapeScene::showLandscape( const Core::LandscapeModel::ILandscape& _landscape )
{
	for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( unsigned int j = 0; j < _landscape.getHeight(); ++j )
		{
			boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > surfaceItem = _landscape.getSurfaceItem( i, j );

			QGraphicsPixmapItem* item = addPixmap( m_environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) );
			item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
		}
	}

} // LandscapeScene::showLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
