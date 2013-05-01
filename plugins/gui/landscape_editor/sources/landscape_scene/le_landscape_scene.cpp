
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_scene/le_landscape_scene.hpp"

#include "landscape_editor/sources/landscape_editor/le_ilandscape_editor_internal.hpp"
#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_iunit.hpp"

#include "le_landscape_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

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
LandscapeScene::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	setNewItemInPosition( _mouseEvent->scenePos() );

	QGraphicsScene::mousePressEvent( _mouseEvent );

} // LandscapeScene::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	setNewItemInPosition( _mouseEvent->scenePos() );

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	emit landscapeWasChanged();

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseReleaseEvent


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
		landscape = m_environment.getGUILandscapeEditor()->getEditableLandscape();

	if ( landscape )
	{
		for ( unsigned int i = 0; i < landscape->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < landscape->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
					surfaceItem = landscape->getSurfaceItem( Plugins::Core::LandscapeModel::Point( i, j ) );

				QGraphicsPixmapItem* item = addPixmap( m_environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) );
				item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
				item->setZValue( 0 );
			}
		}
	}

} // LandscapeScene::regenerateSurfaceLayer


/*---------------------------------------------------------------------------*/


void
LandscapeScene::regenerateObjectsLayer()
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape >
		landscape = m_environment.getGUILandscapeEditor()->getEditableLandscape();

	if ( landscape )
	{
		Plugins::Core::LandscapeModel::ILandscape::UnitsIteratorPtr
			unitsIterator = landscape->getUnitsIterator();

		while ( unitsIterator->isValid() )
		{
			QGraphicsPixmapItem* item = addPixmap(
				m_environment.getPixmap( unitsIterator->current()->getBundlePath(), unitsIterator->current()->getRectInBundle() ) );

			Plugins::Core::LandscapeModel::Point position = landscape->getUnitPosition( unitsIterator->current() );

			qreal posByX = position.m_x * Resources::Landscape::CellSize;
			qreal posByY = position.m_y * Resources::Landscape::CellSize;

			if ( static_cast< unsigned int >( unitsIterator->current()->getRectInBundle().width() ) > Resources::Landscape::CellSize )
			{
				posByX -= ( unitsIterator->current()->getRectInBundle().width() - Resources::Landscape::CellSize ) / 2;
			}

			if ( static_cast< unsigned int >( unitsIterator->current()->getRectInBundle().height() ) > Resources::Landscape::CellSize )
			{
				posByY -= ( unitsIterator->current()->getRectInBundle().height() - Resources::Landscape::CellSize ) / 2;
			}

			item->setPos( posByX, posByY );
			item->setZValue( 1 );

			unitsIterator->next();
		}
	}

} // LandscapeScene::regenerateObjectsLayer


/*---------------------------------------------------------------------------*/


void
LandscapeScene::setCorrectSceneSize()
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape >
		landscape = m_environment.getGUILandscapeEditor()->getEditableLandscape();

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


void
LandscapeScene::setNewItemInPosition( const QPointF& _position )
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape >
		landscape = m_environment.getGUILandscapeEditor()->getEditableLandscape();

	if ( landscape )
	{
		QList< QGraphicsItem* > items = this->items( _position, Qt::ContainsItemShape, Qt::AscendingOrder );

		if ( items.isEmpty() )
		{
			return;
		}

		QPointF itemPos = items[0]->scenePos();
		removeItem( items[0] );

		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > surfaceItem
			= m_environment.getGUILandscapeEditor()->getSelectedSurfaceItem();

		m_environment.getGUILandscapeEditor()->getEditableLandscape()->setSurfaceItem(
				Plugins::Core::LandscapeModel::Point( itemPos.x() / Resources::Landscape::CellSize, itemPos.y() / Resources::Landscape::CellSize )
			,	surfaceItem );

		QGraphicsPixmapItem* newItem = addPixmap( m_environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) );
		newItem->setPos( itemPos );
		newItem->setZValue( 0 );
	}

} // LandscapeScene::setNewItemInPosition


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
