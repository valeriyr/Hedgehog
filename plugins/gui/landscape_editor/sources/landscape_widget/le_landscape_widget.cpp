
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_widget/le_landscape_widget.hpp"

#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"
#include "landscape_editor/sources/landscape_renderer/le_ilandscape_renderer.hpp"
#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeWidget::LandscapeWidget(
		const ILandscapeEditorController& _landscapeEditorController
	,	ILandscapeRenderer& _landscapeRenderer
	,	QWidget* _parent
	)
	:	QGLWidget( QGLFormat( QGL::SampleBuffers ), _parent )
	,	m_landscapeEditorController( _landscapeEditorController )
	,	m_landscapeRenderer( _landscapeRenderer )
	,	m_surfaceLayer()
	,	m_objectsLayer()
{
} // LandscapeWidget::LandscapeWidget


/*---------------------------------------------------------------------------*/


LandscapeWidget::~LandscapeWidget()
{
} // LandscapeWidget::~LandscapeWidget


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::landscapeWasOpened()
{
	regenerate();

	setVisible( true );

} // LandscapeWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::setDefaultLandscape()
{
	setVisible( false );
	setFixedSize( 0, 0 );

} // LandscapeWidget::setDefaultLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::mouseDoubleClickEvent ( QMouseEvent* _event )
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	const unsigned int width = _event->pos().x() / Resources::Landscape::CellSize;
	const unsigned int height = _event->pos().y() / Resources::Landscape::CellSize;

	switch( landscape->getSurfaceItem( width, height ) )
	{
	case Plugins::Core::LandscapeModel::SurfaceItems::Grass:
		landscape->setSurfaceItem( width, height, Plugins::Core::LandscapeModel::SurfaceItems::Snow );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Snow:
		landscape->setSurfaceItem( width, height, Plugins::Core::LandscapeModel::SurfaceItems::Water );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Water:
		landscape->setSurfaceItem( width, height, Plugins::Core::LandscapeModel::SurfaceItems::Grass );
		break;
	default:
		assert( !"Unrecognized surface item" );
		break;
	}

	regenerateSurfaceLayer();
	update();

} // LandscapeWidget::mouseDoubleClickEvent


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::paintEvent( QPaintEvent* _event )
{
	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surfaceLayer );
	painter.drawPixmap( 0, 0, m_objectsLayer );

} // LandscapeWidget::paintEvent


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerate()
{
	regenerateSurfaceLayer();
	regenerateObjectsLayer();

	setFixedSize( m_surfaceLayer.size() );

} // LandscapeWidget::regenerate


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerateSurfaceLayer()
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	m_landscapeRenderer.renderSurface( *landscape, m_surfaceLayer );
}


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerateObjectsLayer()
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	m_landscapeRenderer.renderObjects( *landscape, m_objectsLayer );
}


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
