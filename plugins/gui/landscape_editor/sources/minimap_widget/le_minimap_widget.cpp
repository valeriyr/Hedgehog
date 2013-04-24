
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/minimap_widget/le_minimap_widget.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"
#include "landscape_editor/sources/landscape_renderer/le_ilandscape_renderer.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


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

	m_visibleArea = QRect( 0, 0, m_surfaceLayer.width() * 0.3, m_surfaceLayer.height() * 0.2 );

	update();

} // MinimapWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
MinimapWidget::setDefaultLandscape()
{
	m_surfaceLayer.fill(Qt::white);
	m_objectsLayer.fill(Qt::transparent);

	update();

} // MinimapWidget::setDefaultLandscape


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

} // MinimapWidget::wasClickedOnWidget


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
