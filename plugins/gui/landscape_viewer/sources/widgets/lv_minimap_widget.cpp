
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_minimap_widget.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

#include "lv_minimap_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


MinimapWidget::MinimapWidget( const IEnvironment& _environment,	QWidget* _parent )
	:	QWidget( _parent )
	,	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_surfaceLayer( IMapPreviewGenerator::ms_fixedWidgetSize )
	,	m_objectsLayer( IMapPreviewGenerator::ms_fixedWidgetSize )
	,	m_visibleArea( 0, 0, 0, 0 )
{
	setFixedSize( IMapPreviewGenerator::ms_fixedWidgetSize );

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
							,	Framework::Core::Settings::Events::SettingChanged::Type
							,	boost::bind( &MinimapWidget::onSettingChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectAdded::Type
							,	boost::bind( &MinimapWidget::onObjectWereChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectRemoved::Type
							,	boost::bind( &MinimapWidget::onObjectWereChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::SurfaceItemChanged::Type
							,	boost::bind( &MinimapWidget::onSurfaceItemChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectMoved::Type
							,	boost::bind( &MinimapWidget::onObjectWereChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::BuilderHasStartedBuild::Type
							,	boost::bind( &MinimapWidget::onObjectWereChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::BuilderHasFinishedBuild::Type
							,	boost::bind( &MinimapWidget::onObjectWereChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::HolderHasStartedCollect::Type
							,	boost::bind( &MinimapWidget::onObjectWereChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::HolderHasStopCollect::Type
							,	boost::bind( &MinimapWidget::onObjectWereChanged, this, _1 ) );

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
	m_visibleArea
		= QRect(	m_visibleArea.x()
				,	m_visibleArea.y()
				,	IMapPreviewGenerator::ms_fixedWidgetSize.width() * _visibleWidth
				,	IMapPreviewGenerator::ms_fixedWidgetSize.height() * _visibleHeight );
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
	const QString key = _event.getMember< QString >( Framework::Core::Settings::Events::SettingChanged::Key );

	if ( key == Resources::Properties::SkinId || key == Resources::Properties::UpdateMinimap )
	{
		regenerate();
	}

} // MinimapWidget::onSettingChanged


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event )
{
	regenerate();

} // MinimapWidget::onSurfaceItemChanged


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onObjectWereChanged( const Framework::Core::EventManager::Event& _event )
{
	renderObjects();
	update();

} // MinimapWidget::onObjectWereChanged


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
MinimapWidget::renderSurface()
{
	if ( !m_environment.getBool( Resources::Properties::UpdateMinimap ) )
		return;

	m_environment.generateMapPreview( m_surfaceLayer, IMapPreviewGenerator::GenerateLayers::Surface );

} // MinimapWidget::renderSurface


/*---------------------------------------------------------------------------*/


void
MinimapWidget::renderObjects()
{
	if ( !m_environment.getBool( Resources::Properties::UpdateMinimap ) )
		return;

	m_environment.generateMapPreview( m_objectsLayer, IMapPreviewGenerator::GenerateLayers::Objects );

} // MinimapWidget::renderObjects


/*---------------------------------------------------------------------------*/


void
MinimapWidget::regenerate()
{
	renderSurface();
	renderObjects();
	update();

} // MinimapWidget::regenerate


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
