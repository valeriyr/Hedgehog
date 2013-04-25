
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/minimap_widget/le_minimap_widget.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"
#include "landscape_editor/sources/landscape_renderer/le_ilandscape_renderer.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "le_minimap_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


const QSize MinimapWidget::ms_fixedWidgetSize = QSize( 300, 200 );


/*---------------------------------------------------------------------------*/


MinimapWidget::MinimapWidget(
		const ILandscapeEditorController& _landscapeEditorController
	,	ILandscapeRenderer& _landscapeRenderer
	,	QWidget* _parent
	)
	:	QGLWidget( QGLFormat( QGL::SampleBuffers ), _parent )
	,	m_landscapeEditorController( _landscapeEditorController )
	,	m_landscapeRenderer( _landscapeRenderer )
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
	boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
		landscape = m_landscapeEditorController.getEditableLandscape();

	QPixmap surfaceLayer
		= QPixmap( QSize(
				landscape->getWidth() * Resources::Landscape::CellSize
			,	landscape->getHeight() * Resources::Landscape::CellSize ) );

	QPixmap objectsLayer( surfaceLayer.size() );

	m_landscapeRenderer.renderSurface( *landscape, surfaceLayer );
	m_landscapeRenderer.renderObjects( *landscape, objectsLayer );

	m_surfaceLayer = surfaceLayer.scaled( ms_fixedWidgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
	m_objectsLayer = objectsLayer.scaled( ms_fixedWidgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

	update();

} // MinimapWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
MinimapWidget::setDefaultLandscape()
{
	m_surfaceLayer.fill(Qt::white);
	m_objectsLayer.fill(Qt::transparent);

	m_visibleArea = QRect();

	update();

} // MinimapWidget::setDefaultLandscape


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onLandscapeSceneLoaded( const float _visibleWidth, const float _visibleHeight )
{
	m_visibleArea = QRect( 0, 0, ms_fixedWidgetSize.width() * _visibleWidth, ms_fixedWidgetSize.height() * _visibleHeight );

} // MinimapWidget::onLandscapeSceneLoaded


/*---------------------------------------------------------------------------*/


void
MinimapWidget::onVisibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight )
{
	m_visibleArea
		= QRect(
				( width() - m_visibleArea.width() ) * _visibleWidth
			,	( height() - m_visibleArea.height() ) * _visibleHeight
			,	m_visibleArea.width()
			,	m_visibleArea.height() );

	update();

} // MinimapWidget::onVisibleRectOfLandscapeViewWasChanged


/*---------------------------------------------------------------------------*/


void
MinimapWidget::paintEvent( QPaintEvent* _event )
{
	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surfaceLayer );
	painter.drawPixmap( 0, 0, m_objectsLayer );

	painter.drawRect( m_visibleArea );

	QGLWidget::paintEvent( _event );

} // MinimapWidget::paintEvent


/*---------------------------------------------------------------------------*/


void
MinimapWidget::mousePressEvent ( QMouseEvent* _event )
{
	wasClickedOnWidget( _event->pos() );
	update();

	QGLWidget::mousePressEvent( _event );

} // MinimapWidget::mousePressEvent


/*---------------------------------------------------------------------------*/


void
MinimapWidget::mouseMoveEvent ( QMouseEvent* _event )
{
	wasClickedOnWidget( _event->pos() );
	update();

	QGLWidget::mouseMoveEvent( _event );

} // MinimapWidget::mouseMoveEvent


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

	emit visibleAreaRectWasChanged(
			static_cast< float >( m_visibleArea.left() ) / ( width() - m_visibleArea.width() )
		,	static_cast< float >( m_visibleArea.top() ) / ( height() - m_visibleArea.height() ) );

} // MinimapWidget::wasClickedOnWidget


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
