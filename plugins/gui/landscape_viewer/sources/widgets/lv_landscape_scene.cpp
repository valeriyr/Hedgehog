
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

#include "lv_landscape_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeScene::LandscapeScene( const IEnvironment& _environment, QObject* _parent )
	:	QGraphicsScene( _parent )
	,	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
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
		m_selectionItem->setZValue( ObjectZValue::SelectionRect );
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

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Framework::Core::Settings::Events::SettingChanged::ms_type
							,	boost::bind( &LandscapeScene::onSettingChanged, this, _1 ) );

} // LandscapeScene::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasClosed()
{
	m_subscriber.unsubscribe();

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
LandscapeScene::onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& _id )
{
	/*if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		return;

	boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, _id );

	if ( !surfaceItemGraphicsInfo )
		return;

	m_surfaceItemId = _id;
	m_objectName.clear();

	if ( m_currentEditorItem )
		delete m_currentEditorItem;

	m_currentEditorItem
		= new QGraphicsPixmapItem( m_environment.getPixmap( surfaceItemGraphicsInfo->getAtlasName(), surfaceItemGraphicsInfo->getFrameRect() ) );

	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
	opacityEffect->setOpacity( 0.5 );

	m_currentEditorItem->setGraphicsEffect( opacityEffect );

	addItem( m_currentEditorItem );

	m_currentEditorItem->setZValue( ObjectZValue::CurrentSurfaceItem );
	m_currentEditorItem->setPos( 0, 0 );*/

} // LandscapeScene::onChangeSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onChangeObject( const QString& _name )
{
	/*if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		return;

	boost::intrusive_ptr< IObjectGraphicsInfo >
		objectGraphicsInfo = m_environment.getObjectGraphicsInfo( Resources::Landscape::SkinId, _name );

	if ( !objectGraphicsInfo )
		return;

	m_objectName = _name;
	m_surfaceItemId = Plugins::Core::LandscapeModel::ISurfaceItem::ms_invalidTypeId;

	if ( m_currentEditorItem )
		delete m_currentEditorItem;

	m_currentEditorItem
		= new QGraphicsPixmapItem( m_environment.getPixmap( objectGraphicsInfo->getAtlasName(), objectGraphicsInfo->getFrameRect() ) );

	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
	opacityEffect->setOpacity( 0.5 );

	m_currentEditorItem->setGraphicsEffect( opacityEffect );

	addItem( m_currentEditorItem );

	m_currentEditorItem->setZValue( ObjectZValue::CurrentSurfaceItem );
	m_currentEditorItem->setPos( 0, 0 );*/

} // LandscapeScene::onChangeObject


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onMousePossitionWasChanged( const QPointF& _point )
{
	/*if ( m_currentEditorItem )
	{
		qreal xpos = _point.x() < 0 ? 0 : ( static_cast< int >( _point.x() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );
		qreal ypos = _point.y() < 0 ? 0 : ( static_cast< int >( _point.y() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );

		if ( m_objectName.isEmpty() )
		{
			if ( xpos > width() - Resources::Landscape::CellSize )
				xpos = width() - Resources::Landscape::CellSize;

			if ( ypos > height() - Resources::Landscape::CellSize )
				ypos = height() - Resources::Landscape::CellSize;
		}
		else
		{
			boost::intrusive_ptr< IObjectGraphicsInfo >
				objectGraphicsInfo = m_environment.getObjectGraphicsInfo( Resources::Landscape::SkinId, m_objectName );

			if ( !objectGraphicsInfo )
				return;

			if ( static_cast< unsigned int >( objectGraphicsInfo->getFrameRect().width() ) > Resources::Landscape::CellSize )
			{
				xpos -= ( objectGraphicsInfo->getFrameRect().width() - Resources::Landscape::CellSize ) / 2;
			}

			if ( static_cast< unsigned int >( objectGraphicsInfo->getFrameRect().height() ) > Resources::Landscape::CellSize )
			{
				ypos -= ( objectGraphicsInfo->getFrameRect().height() - Resources::Landscape::CellSize ) / 2;
			}

			if ( xpos > width() - objectGraphicsInfo->getFrameRect().width() )
				xpos = width() - Resources::Landscape::CellSize - ( objectGraphicsInfo->getFrameRect().width() - Resources::Landscape::CellSize ) / 2;

			if ( ypos > height() - objectGraphicsInfo->getFrameRect().height() )
				ypos = height() - Resources::Landscape::CellSize - ( objectGraphicsInfo->getFrameRect().width() - Resources::Landscape::CellSize ) / 2;
		}

		m_currentEditorItem->setPos( xpos, ypos );
	}*/

} // LandscapeScene::onMousePossitionWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onSettingChanged( const Framework::Core::EventManager::Event& _event )
{
	clear();
	generateLandscape();

} // LandscapeScene::onSettingChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::generateLandscape()
{
	bool showTarrain = m_environment.getBool( Resources::Properties::TerrainMapVisibility );

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
				item->setZValue( ObjectZValue::Surface );

				if ( showTarrain )
				{
					Plugins::Core::LandscapeModel::TerrainMapData
						terrainMapData = handle->getLandscape()->getTerrainMapData( QPoint( i, j ) );

					QColor color;

					if ( terrainMapData.m_engagedWithGround )
					{
						color = QColor( 255, 0, 255 );
					}
					else if ( terrainMapData.m_engagedWithAir )
					{
						color = QColor( 0, 255, 255 );
					}
					else if ( terrainMapData.m_terrainMapItem == Plugins::Core::LandscapeModel::TerrainMapItem::Ground )
					{
						color = QColor( 0, 255, 0 );
					}
					else if ( terrainMapData.m_terrainMapItem == Plugins::Core::LandscapeModel::TerrainMapItem::NotAvailable )
					{
						color = QColor( 255, 0, 0 );
					}
					else if ( terrainMapData.m_terrainMapItem == Plugins::Core::LandscapeModel::TerrainMapItem::Water )
					{
						color = QColor( 0, 0, 255 );
					}
					else
					{
						assert( !"Unknown terrain map item!" );
					}

					QPixmap pixmap( QSize( Resources::Landscape::CellSize, Resources::Landscape::CellSize ) );
					pixmap.fill( color );

					QGraphicsPixmapItem* item = new QGraphicsPixmapItem( pixmap );

					item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
					item->setZValue( ObjectZValue::Terrain );

					QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
					opacityEffect->setOpacity( 0.4 );

					item->setGraphicsEffect( opacityEffect );

					addItem( item );
				}
			}
		}

		/*Plugins::Core::LandscapeModel::ILandscape::UnitsIteratorPtr
			unitsIterator = m_landscape->getUnitsIterator();

		while ( unitsIterator->isValid() )
		{
			QGraphicsPixmapItem* item = addPixmap(
				m_environment.getPixmap( unitsIterator->current()->getBundlePath(), unitsIterator->current()->getRectInBundle() ) );

			updatePosition( unitsIterator->current(), item );

			item->setZValue( ObjectZValue::Object );

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
