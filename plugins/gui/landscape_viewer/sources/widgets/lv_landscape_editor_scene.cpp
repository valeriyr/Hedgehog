
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_iunit.hpp"

#include "lv_landscape_editor_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeEditorScene::LandscapeEditorScene( const IEnvironment& _environment, QObject* _parent )
	:	QGraphicsScene( _parent )
	,	m_environment( _environment )
	,	m_landscape()
	,	m_surfaceItem( _environment.getDefaultSurfaceItem() )
{
} // LandscapeEditorScene::LandscapeEditorScene


/*---------------------------------------------------------------------------*/


LandscapeEditorScene::~LandscapeEditorScene()
{
} // LandscapeEditorScene::~LandscapeEditorScene


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::landscapeWasOpened(
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape > _landscape )
{
	m_landscape = _landscape;
	regenerate();

} // LandscapeEditorScene::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::landscapeWasClosed()
{
	m_landscape.reset();
	regenerate();

} // LandscapeEditorScene::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	setNewItemInPosition( _mouseEvent->scenePos() );

	QGraphicsScene::mousePressEvent( _mouseEvent );

} // LandscapeEditorScene::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	setNewItemInPosition( _mouseEvent->scenePos() );

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeEditorScene::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	emit landscapeWasChanged();

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeEditorScene::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::onChangeSurfaceItem(
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > _surfaceItem )
{
	m_surfaceItem = _surfaceItem;

} // LandscapeEditorScene::onChangeSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::regenerate()
{
	clear();

	regenerateSurfaceLayer();
	regenerateObjectsLayer();

	setCorrectSceneSize();

} // LandscapeEditorScene::regenerate


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::regenerateSurfaceLayer()
{
	if ( m_landscape )
	{
		for ( unsigned int i = 0; i < m_landscape->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < m_landscape->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
					surfaceItem = m_landscape->getSurfaceItem( Plugins::Core::LandscapeModel::Point( i, j ) );

				QGraphicsPixmapItem* item = addPixmap( m_environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) );
				item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
				item->setZValue( 0 );
			}
		}
	}

} // LandscapeEditorScene::regenerateSurfaceLayer


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::regenerateObjectsLayer()
{
	if ( m_landscape )
	{
		Plugins::Core::LandscapeModel::ILandscape::UnitsIteratorPtr
			unitsIterator = m_landscape->getUnitsIterator();

		while ( unitsIterator->isValid() )
		{
			QGraphicsPixmapItem* item = addPixmap(
				m_environment.getPixmap( unitsIterator->current()->getBundlePath(), unitsIterator->current()->getRectInBundle() ) );

			Plugins::Core::LandscapeModel::Point position = m_landscape->getUnitPosition( unitsIterator->current() );

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

} // LandscapeEditorScene::regenerateObjectsLayer


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::setCorrectSceneSize()
{
	if ( m_landscape )
	{
		setSceneRect( 0, 0, m_landscape->getWidth() * Resources::Landscape::CellSize, m_landscape->getHeight() * Resources::Landscape::CellSize );
	}
	else
	{
		setSceneRect( 0, 0, 0, 0 );
	}

} // LandscapeEditorScene::setCorrectSceneSize


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::setNewItemInPosition( const QPointF& _position )
{
	if ( m_landscape )
	{
		QList< QGraphicsItem* > items = this->items( _position, Qt::ContainsItemShape, Qt::AscendingOrder );

		if ( items.isEmpty() )
		{
			return;
		}

		QPointF itemPos = items[0]->scenePos();
		removeItem( items[0] );

		m_landscape->setSurfaceItem(
				Plugins::Core::LandscapeModel::Point( itemPos.x() / Resources::Landscape::CellSize, itemPos.y() / Resources::Landscape::CellSize )
			,	m_surfaceItem );

		QGraphicsPixmapItem* newItem = addPixmap( m_environment.getPixmap( m_surfaceItem->getBundlePath(), m_surfaceItem->getRectInBundle() ) );
		newItem->setPos( itemPos );
		newItem->setZValue( 0 );
	}

} // LandscapeEditorScene::setNewItemInPosition


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
