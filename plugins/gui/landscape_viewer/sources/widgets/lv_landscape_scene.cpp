
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "lv_landscape_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeScene::LandscapeScene( const IEnvironment& _environment, QObject* _parent )
	:	QGraphicsScene( _parent )
	,	m_environment( _environment )
	,	m_startSelectionPoint()
	,	m_selectionItem( NULL )
	//,	m_unitsCollection()
{
} // LandscapeScene::LandscapeScene


/*---------------------------------------------------------------------------*/


LandscapeScene::~LandscapeScene()
{
} // LandscapeScene::~LandscapeScene


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if (	_mouseEvent->buttons() == Qt::LeftButton
		&&	_mouseEvent->scenePos().x() >= 0
		&&	_mouseEvent->scenePos().y() >= 0
		&&	_mouseEvent->scenePos().x() <= width()
		&&	_mouseEvent->scenePos().y() <= height() )
	{
		m_selectionItem = addRect( 0, 0, 0, 0 );
		m_selectionItem->setPos( _mouseEvent->scenePos().x(), _mouseEvent->scenePos().y() );
		m_selectionItem->setZValue( 3 );
		m_startSelectionPoint = _mouseEvent->scenePos();
	}

	QGraphicsScene::mousePressEvent( _mouseEvent );

} // LandscapeScene::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( m_selectionItem )
	{
		qreal posByX = m_startSelectionPoint.x();
		qreal posByY = m_startSelectionPoint.y();

		qreal mounsePosByX = _mouseEvent->scenePos().x() < 0 ? 0 : _mouseEvent->scenePos().x();
		qreal mounsePosByY = _mouseEvent->scenePos().y() < 0 ? 0 : _mouseEvent->scenePos().y();

		qreal width = mounsePosByX - m_startSelectionPoint.x();
		qreal height = mounsePosByY - m_startSelectionPoint.y();

		if ( width < 0 )
		{
			posByX += width;
			width = -width;
		}

		if ( height < 0 )
		{
			posByY += height;
			height = -height;
		}

		if ( posByX + width >= this->width() )
		{
			width = this->width() - posByX - 1;
		}

		if ( posByY + height >= this->height() )
		{
			height = this->height() - posByY - 1;
		}

		m_selectionItem->setPos( posByX, posByY );

		m_selectionItem->setRect( 0, 0, width, height );
	}

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( m_selectionItem )
	{
		m_environment.selectItemsInModel(
				LandscapeScene::convertFromScenePosition( m_selectionItem->scenePos() )
			,	LandscapeScene::convertFromScenePosition( m_selectionItem->scenePos() ) );

		removeItem( m_selectionItem );
		delete m_selectionItem;
		m_selectionItem = NULL;
		m_startSelectionPoint = QPointF();
	}
	else
	{
		m_environment.moveSelectedItems( LandscapeScene::convertFromScenePosition( _mouseEvent->scenePos() ) );
	}

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasOpened()
{
	generateLandscape();

} // LandscapeScene::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasClosed()
{
	clear();
	setSceneRect( 0, 0, 0, 0 );

} // LandscapeScene::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onUpdateTimerFired()
{
	/*UnitsCollectionIterator
			begin = m_unitsCollection.begin()
		,	end = m_unitsCollection.end();

	for ( ; begin != end; ++begin )
	{
		updatePosition( begin->first, begin->second );
		begin->second->setGraphicsEffect( NULL );
	}

	if ( m_landscape->getSelectedUnit() )
	{
		UnitsCollectionIterator iterator
			= m_unitsCollection.find( m_landscape->getSelectedUnit() );

		assert( iterator != m_unitsCollection.end() );

		iterator->second->setGraphicsEffect( new QGraphicsColorizeEffect() );
	}*/

} // LandscapeScene::onUpdateTimerFired


/*---------------------------------------------------------------------------*/


void
LandscapeScene::generateLandscape()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		for ( unsigned int i = 0; i < handle->getLandscape()->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < handle->getLandscape()->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
					surfaceItem = handle->getLandscape()->getSurfaceItem( QPoint( i, j ) );

				boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
					surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, surfaceItem->getId() );

				QGraphicsPixmapItem* item = addPixmap( m_environment.getPixmap( surfaceItemGraphicsInfo->getAtlasName(), surfaceItemGraphicsInfo->getFrameRect() ) );
				item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
				item->setZValue( 0 );
			}
		}

		/*Plugins::Core::LandscapeModel::ILandscape::UnitsIteratorPtr
			unitsIterator = m_landscape->getUnitsIterator();

		while ( unitsIterator->isValid() )
		{
			QGraphicsPixmapItem* item = addPixmap(
				m_environment.getPixmap( unitsIterator->current()->getBundlePath(), unitsIterator->current()->getRectInBundle() ) );

			updatePosition( unitsIterator->current(), item );

			item->setZValue( 1 );

			m_unitsCollection.insert( std::make_pair( unitsIterator->current(), item ) );

			unitsIterator->next();
		}*/
	}

} // LandscapeScene::generateLandscape


/*---------------------------------------------------------------------------*/

/*
void
LandscapeScene::updatePosition(
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::IUnit > _unit
	,	QGraphicsPixmapItem* _graphicsItem )
{
	QPoint position = m_landscape->getUnitPosition( _unit );

	qreal posByX = position.x() * Resources::Landscape::CellSize;
	qreal posByY = position.y() * Resources::Landscape::CellSize;

	if ( static_cast< unsigned int >( _unit->getRectInBundle().width() ) > Resources::Landscape::CellSize )
	{
		posByX -= ( _unit->getRectInBundle().width() - Resources::Landscape::CellSize ) / 2;
	}

	if ( static_cast< unsigned int >( _unit->getRectInBundle().height() ) > Resources::Landscape::CellSize )
	{
		posByY -= ( _unit->getRectInBundle().height() - Resources::Landscape::CellSize ) / 2;
	}

	_graphicsItem->setPos( posByX, posByY );

} // LandscapeScene::updatePosition
*/

/*---------------------------------------------------------------------------*/


QPoint
LandscapeScene::convertFromScenePosition( const QPointF& _scenePosition )
{
	return
		QPoint(
				_scenePosition.x() / Resources::Landscape::CellSize
			,	_scenePosition.y() / Resources::Landscape::CellSize );

} // LandscapeScene::convertFromScenePosition


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
