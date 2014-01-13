
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_minimap_widget.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"

#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

#include "lv_minimap_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


const QSize MinimapWidget::ms_fixedWidgetSize = QSize( 300, 200 );


/*---------------------------------------------------------------------------*/


MinimapWidget::MinimapWidget( const IEnvironment& _environment,	QWidget* _parent )
	:	QWidget( _parent )
	,	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_surfaceLayer( ms_fixedWidgetSize )
	,	m_objectsLayer( ms_fixedWidgetSize )
	,	m_visibleArea( 0, 0, 0, 0 )
{
	setFixedSize( ms_fixedWidgetSize );

	m_surfaceLayer.fill(Qt::white);
	m_objectsLayer.fill(Qt::transparent);

} // MinimapWidget::MinimapWidget


/*---------------------------------------------------------------------------*/


MinimapWidget::~MinimapWidget()
{
} // MinimapWidget::~MinimapWidget


/*---------------------------------------------------------------------------*/


void
MinimapWidget::landscapeWasOpened()
{
	regenerate();

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Framework::Core::Settings::Events::SettingChanged::ms_type
							,	boost::bind( &MinimapWidget::onSettingChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_type
							,	boost::bind( &MinimapWidget::onObjectCreated, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_type
							,	boost::bind( &MinimapWidget::onSurfaceItemChanged, this, _1 ) );


	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_type
							,	boost::bind( &MinimapWidget::onObjectMoved, this, _1 ) );

} // MinimapWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
MinimapWidget::landscapeWasClosed()
{
	m_subscriber.unsubscribe();

	m_surfaceLayer.fill(Qt::white);
	m_objectsLayer.fill(Qt::transparent);

	m_visibleArea = QRect();

	update();

} // MinimapWidget::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onChangeVisibilityRectSize( const float _visibleWidth, const float _visibleHeight )
{
	m_visibleArea = QRect( m_visibleArea.x(), m_visibleArea.y(), ms_fixedWidgetSize.width() * _visibleWidth, ms_fixedWidgetSize.height() * _visibleHeight );
	update();

} // MinimapWidget::onChangeVisibilityRectSize


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onChangeVisibilityRectPosition( const float _visibleWidth, const float _visibleHeight )
{
	m_visibleArea
		= QRect(
				( width() - m_visibleArea.width() ) * _visibleWidth
			,	( height() - m_visibleArea.height() ) * _visibleHeight
			,	m_visibleArea.width()
			,	m_visibleArea.height() );

	update();

} // MinimapWidget::onChangeVisibilityRectPosition



/*---------------------------------------------------------------------------*/


void
MinimapWidget::paintEvent( QPaintEvent* _event )
{
	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surfaceLayer );
	painter.drawPixmap( 0, 0, m_objectsLayer );

	painter.setPen( QPen( QColor( 0, 184, 217 ) ) );
	painter.drawRect( m_visibleArea );

} // MinimapWidget::paintEvent


/*---------------------------------------------------------------------------*/


void
MinimapWidget::mousePressEvent ( QMouseEvent* _event )
{
	wasClickedOnWidget( _event->pos() );
	update();

} // MinimapWidget::mousePressEvent


/*---------------------------------------------------------------------------*/


void
MinimapWidget::mouseMoveEvent ( QMouseEvent* _event )
{
	wasClickedOnWidget( _event->pos() );
	update();

} // MinimapWidget::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onSettingChanged( const Framework::Core::EventManager::Event& _event )
{
	if (	_event.getAttribute( Framework::Core::Settings::Events::SettingChanged::ms_key ).toString()
		==	Resources::Properties::SkinId )
	{
		regenerate();
	}

} // MinimapWidget::onSettingChanged


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onObjectCreated( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	renderObjects( *handle->getLandscape() );

	update();

} // MinimapWidget::onObjectCreated


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event )
{
	regenerate();

} // MinimapWidget::onSurfaceItemChanged


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onObjectMoved( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	renderObjects( *handle->getLandscape() );

	update();

} // MinimapWidget::onObjectMoved


/*---------------------------------------------------------------------------*/


void
MinimapWidget::wasClickedOnWidget( const QPoint& _atPoint )
{
	QPoint visibleAreaOrigin( m_visibleArea.topLeft() );

	if ( _atPoint.x() - m_visibleArea.width() / 2 < 0 )
	{
		visibleAreaOrigin.setX( 1 );
	}
	else if ( _atPoint.x() + m_visibleArea.width() / 2 > size().width() )
	{
		visibleAreaOrigin.setX( size().width() - m_visibleArea.width() );
	}
	else
	{
		visibleAreaOrigin.setX( _atPoint.x() - m_visibleArea.width() / 2 );
	}

	if ( _atPoint.y() - m_visibleArea.height() / 2 < 0 )
	{
		visibleAreaOrigin.setY( 0 );
	}
	else if ( _atPoint.y() + m_visibleArea.height() / 2 > size().height() )
	{
		visibleAreaOrigin.setY( size().height() - m_visibleArea.height() - 1 );
	}
	else
	{
		visibleAreaOrigin.setY( _atPoint.y() - m_visibleArea.height() / 2 );
	}

	m_visibleArea.moveTo( visibleAreaOrigin );

	emit visibilityRectChangedPosition(
			static_cast< float >( m_visibleArea.left() ) / ( width() - m_visibleArea.width() )
		,	static_cast< float >( m_visibleArea.top() ) / ( height() - m_visibleArea.height() ) );

} // MinimapWidget::wasClickedOnWidget


/*---------------------------------------------------------------------------*/


void
MinimapWidget::renderSurface( const Core::LandscapeModel::ILandscape& _landscape )
{
	QPixmap surfaceLayer
		= QPixmap( QSize(
				_landscape.getWidth() * Resources::Landscape::CellSize
			,	_landscape.getHeight() * Resources::Landscape::CellSize ) );

	QPainter painter;
	painter.begin( &surfaceLayer );
	painter.setRenderHint( QPainter::Antialiasing );

	for ( int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
				surfaceItem = _landscape.getSurfaceItem( QPoint( i, j ) );

			boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
				surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo(
						m_environment.getString( Resources::Properties::SkinId )
					,	surfaceItem->getId() );

			painter.drawPixmap(
				QRect(
						i * Resources::Landscape::CellSize
					,	j * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize )
					,	m_environment.getPixmap(
								surfaceItemGraphicsInfo->getAtlasName()
							,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );
		}
	}

	m_surfaceLayer = surfaceLayer.scaled( ms_fixedWidgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

} // MinimapWidget::renderSurface


/*---------------------------------------------------------------------------*/


void
MinimapWidget::renderObjects( const Core::LandscapeModel::ILandscape& _landscape )
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		m_objectsLayer = QPixmap( ms_fixedWidgetSize );

		m_objectsLayer.fill( Qt::transparent );

		float scaleByX = static_cast< float >( ms_fixedWidgetSize.width() ) / ( _landscape.getWidth() * Resources::Landscape::CellSize );
		float scaleByY = static_cast< float >( ms_fixedWidgetSize.height() ) / ( _landscape.getHeight() * Resources::Landscape::CellSize );

		QPainter painter;
		painter.begin( &m_objectsLayer );
		painter.setRenderHint( QPainter::Antialiasing );

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection objectsCollection;
		handle->getLandscape()->fetchObjects( objectsCollection );

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollectionIterator
				begin = objectsCollection.begin()
			,	end = objectsCollection.end();

		for ( ; begin != end; ++begin )
		{
			boost::intrusive_ptr< Core::LandscapeModel::ILocateComponent > locateComponent
				= ( *begin )->getComponent< Core::LandscapeModel::ILocateComponent >( Plugins::Core::LandscapeModel::ComponentId::Locate );

			for ( int x = locateComponent->getLocation().x(); x < locateComponent->getLocation().x() + locateComponent->getStaticData().m_size.width(); ++x )
			{
				for ( int y = locateComponent->getLocation().y(); y < locateComponent->getLocation().y() + locateComponent->getStaticData().m_size.height(); ++y )
				{
					qreal posByX = ( x * Resources::Landscape::CellSize ) * scaleByX;
					qreal posByY = ( y * Resources::Landscape::CellSize ) * scaleByY;

					QPixmap pixmap( QSize( Resources::Landscape::CellSize * scaleByX, Resources::Landscape::CellSize * scaleByY ) );
					pixmap.fill( QColor( 0, 255, 0 ) );

					painter.drawPixmap(
							QRect( posByX, posByY, pixmap.width(), pixmap.height() )
						,	pixmap );
				}
			}
		}
	}

} // MinimapWidget::renderObjects


/*---------------------------------------------------------------------------*/


void
MinimapWidget::regenerate()
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		renderSurface( *handle->getLandscape() );
		renderObjects( *handle->getLandscape() );
	}

	update();

} // MinimapWidget::regenerate


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
