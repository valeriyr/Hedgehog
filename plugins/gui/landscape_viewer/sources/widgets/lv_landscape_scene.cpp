
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/object_graphics_info/lv_iobject_graphics_info.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_iunit.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_landscape_scene_states.hpp"

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
	,	m_landscapeSceneState( new LandscapeSceneGameState( _environment, *this ) )
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
	m_landscapeSceneState->mousePressEvent( _mouseEvent );

	QGraphicsScene::mousePressEvent( _mouseEvent );

} // LandscapeScene::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	m_landscapeSceneState->mouseMoveEvent( _mouseEvent );

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	m_landscapeSceneState->mouseReleaseEvent( _mouseEvent );

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasOpened()
{
	setCorrectSceneSize();

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
	setCorrectSceneSize();

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
	m_landscapeSceneState.reset( new LandscapeSurfaceItemEditingState( m_environment, *this, _id ) );

} // LandscapeScene::onChangeSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onChangeObject( const QString& _name )
{
	m_landscapeSceneState.reset( new LandscapeObjectEditingState( m_environment, *this, _name ) );

} // LandscapeScene::onChangeObject


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onControlItemSelected()
{
	m_landscapeSceneState.reset( new LandscapeSceneGameState( m_environment, *this ) );

} // LandscapeScene::onControlItemSelected


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onMousePossitionWasChanged( const QPointF& _point )
{
	m_landscapeSceneState->onMousePossitionWasChanged( _point );

} // LandscapeScene::onMousePossitionWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onSettingChanged( const Framework::Core::EventManager::Event& _event )
{
	m_landscapeSceneState->setSceneObjectsVisibility( !m_environment.getBool( Resources::Properties::TerrainMapVisibility ) );
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

		Plugins::Core::LandscapeModel::ILandscape::UnitsCollection unitsCollection;
		handle->getLandscape()->fetchUnits( unitsCollection );

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

} // LandscapeScene::generateLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeScene::setCorrectSceneSize()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		setSceneRect( 0, 0, handle->getLandscape()->getWidth() * Resources::Landscape::CellSize, handle->getLandscape()->getHeight() * Resources::Landscape::CellSize );
	}
	else
	{
		setSceneRect( 0, 0, 0, 0 );
	}

} // LandscapeScene::setCorrectSceneSize


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
