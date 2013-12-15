
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/object_graphics_info/lv_iobject_graphics_info.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_iunit.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

#include "lv_landscape_editor_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


	,	m_surfaceItemId( Plugins::Core::LandscapeModel::ISurfaceItem::ms_invalidTypeId )





/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( _mouseEvent->buttons() & Qt::LeftButton )
		setNewItemInPosition( _mouseEvent->scenePos() );

	QGraphicsScene::mousePressEvent( _mouseEvent );

} // LandscapeEditorScene::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( _mouseEvent->buttons() & Qt::LeftButton )
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
LandscapeEditorScene::regenerate()
{
	delete m_currentEditorItem;
	m_currentEditorItem = NULL;

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
		bool showTarrain = m_environment.getBool( Resources::Properties::TerrainMapVisibility );

		for ( unsigned int i = 0; i < m_landscape->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < m_landscape->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
				surfaceItem = m_landscape->getSurfaceItem( QPoint( i, j ) );

				boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
					surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, surfaceItem->getId() );

				QGraphicsPixmapItem* item = addPixmap( m_environment.getPixmap( surfaceItemGraphicsInfo->getAtlasName(), surfaceItemGraphicsInfo->getFrameRect() ) );
				item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
				item->setZValue( ObjectZValue::Surface );

				if ( showTarrain )
				{
					Plugins::Core::LandscapeModel::TerrainMapData
						terrainMapData = m_landscape->getTerrainMapData( QPoint( i, j ) );

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
	}

} // LandscapeEditorScene::regenerateSurfaceLayer


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::regenerateObjectsLayer()
{
	if ( m_landscape )
	{
		Plugins::Core::LandscapeModel::ILandscape::UnitsCollection unitsCollection;
		m_landscape->fetchUnits( unitsCollection );

		Plugins::Core::LandscapeModel::ILandscape::UnitsCollectionIterator
				begin = unitsCollection.begin()
			,	end = unitsCollection.end();

		for ( ; begin != end; ++begin )
		{
			boost::intrusive_ptr< IObjectGraphicsInfo >
				objectGraphicsInfo = m_environment.getObjectGraphicsInfo( Resources::Landscape::SkinId, ( *begin )->getType()->getName() );

			QGraphicsPixmapItem* item = addPixmap(
				m_environment.getPixmap( objectGraphicsInfo->getAtlasName(), objectGraphicsInfo->getFrameRect() ) );

			QRect position = ( *begin )->getPosition();

			qreal posByX = position.x() * Resources::Landscape::CellSize;
			qreal posByY = position.y() * Resources::Landscape::CellSize;

			if ( static_cast< unsigned int >( objectGraphicsInfo->getFrameRect().width() ) > Resources::Landscape::CellSize )
			{
				posByX -= ( objectGraphicsInfo->getFrameRect().width() - Resources::Landscape::CellSize ) / 2;
			}

			if ( static_cast< unsigned int >( objectGraphicsInfo->getFrameRect().height() ) > Resources::Landscape::CellSize )
			{
				posByY -= ( objectGraphicsInfo->getFrameRect().height() - Resources::Landscape::CellSize ) / 2;
			}

			item->setPos( posByX, posByY );
			item->setZValue( ObjectZValue::Object );
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
		if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
			return;

		QList< QGraphicsItem* > items = this->items( _position, Qt::ContainsItemShape, Qt::AscendingOrder );

		if ( items.isEmpty() )
			return;

		if ( m_objectName.isEmpty() )
		{
			QPointF itemPos = items[ObjectZValue::Surface]->scenePos();
			removeItem( items[ObjectZValue::Surface] );

			m_landscape->setSurfaceItem(
					QPoint( itemPos.x() / Resources::Landscape::CellSize, itemPos.y() / Resources::Landscape::CellSize )
				,	m_surfaceItemId );

			boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
				surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, m_surfaceItemId );

			QGraphicsPixmapItem* newItem = addPixmap( m_environment.getPixmap( surfaceItemGraphicsInfo->getAtlasName(), surfaceItemGraphicsInfo->getFrameRect() ) );
			newItem->setPos( itemPos );
			newItem->setZValue( ObjectZValue::Surface );
		}
		else
		{
			qreal xpos = _position.x() < 0 ? 0 : ( static_cast< int >( _position.x() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );
			qreal ypos = _position.y() < 0 ? 0 : ( static_cast< int >( _position.y() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );

			QRect objectRect( xpos / Resources::Landscape::CellSize, ypos / Resources::Landscape::CellSize, 1, 1 );

			if ( m_landscape->canCreateObject( objectRect, m_objectName ) )
			{
				m_landscape->createObject(
						QRect( xpos / Resources::Landscape::CellSize, ypos / Resources::Landscape::CellSize, 1, 1 )
					,	m_objectName );

				boost::intrusive_ptr< IObjectGraphicsInfo >
					objectGraphicsInfo = m_environment.getObjectGraphicsInfo( Resources::Landscape::SkinId, m_objectName );

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

				QGraphicsPixmapItem* newItem = addPixmap( m_environment.getPixmap( objectGraphicsInfo->getAtlasName(), objectGraphicsInfo->getFrameRect() ) );
				newItem->setPos( QPoint( xpos, ypos ) );
				newItem->setZValue( ObjectZValue::Object );
			}
		}
	}

} // LandscapeEditorScene::setNewItemInPosition


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::onSettingChanged( const Framework::Core::EventManager::Event& _event )
{
	regenerate();

} // LandscapeEditorScene::onSettingChanged


/*---------------------------------------------------------------------------*/

/*
void
LandscapeEditorScene::onObjectCreated( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< IObjectGraphicsInfo >
		objectGraphicsInfo = m_environment.getObjectGraphicsInfo(
				Resources::Landscape::SkinId
			,	_event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectNameAttribute ).toString() );

	QRect objectRect = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectRectAttribute ).toRect();

	qreal posByX = objectRect.x() * Resources::Landscape::CellSize;
	qreal posByY = objectRect.y() * Resources::Landscape::CellSize;

	QGraphicsPixmapItem* newItem = addPixmap( m_environment.getPixmap( objectGraphicsInfo->getAtlasName(), objectGraphicsInfo->getFrameRect() ) );
	newItem->setPos( QPoint( posByX, posByY ) );
	newItem->setZValue( ObjectZValue::Object );

} // LandscapeEditorScene::onObjectCreated*/


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
