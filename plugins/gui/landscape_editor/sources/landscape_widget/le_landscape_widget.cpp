
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_widget/le_landscape_widget.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeWidget::LandscapeWidget( const IEnvironment& _environment, QWidget* _parent )
	:	QGLWidget( QGLFormat( QGL::SampleBuffers ), _parent )
	,	m_environment( _environment )
	,	m_surface()
{
	setDefaultLandscape();

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
	update();

} // LandscapeWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::setDefaultLandscape()
{
	setVisible( false );
	setFixedSize( 0, 0 );
	update();

} // LandscapeWidget::setDefaultLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::paintEvent( QPaintEvent* _event )
{
	QGLWidget::paintEvent( _event );

} // LandscapeWidget::paintEvent


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::mouseDoubleClickEvent ( QMouseEvent* _event )
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_environment.getLandscapeEditorController()->getEditableLandscape();

	Plugins::Core::LandscapeModel::Point point(
			_event->pos().x() / Resources::Landscape::CellSize
		,	_event->pos().y() / Resources::Landscape::CellSize );

	switch( landscape->getSurfaceItem( point ) )
	{
	case Plugins::Core::LandscapeModel::SurfaceItems::Grass:
		landscape->setSurfaceItem( point, Plugins::Core::LandscapeModel::SurfaceItems::Sand );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Sand:
		landscape->setSurfaceItem( point, Plugins::Core::LandscapeModel::SurfaceItems::Snow );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Snow:
		landscape->setSurfaceItem( point, Plugins::Core::LandscapeModel::SurfaceItems::Wather );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Wather:
		landscape->setSurfaceItem( point, Plugins::Core::LandscapeModel::SurfaceItems::Grass );
		break;
	default:
		assert( !"Unrecognized surface item" );
		break;
	}

	regenerate();
	update();

} // LandscapeWidget::mouseDoubleClickEvent


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerate()
{
	regenerateSurface();

	setFixedSize( m_surface.size() );

	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surface );

} // LandscapeWidget::regenerate


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerateSurface()
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_environment.getLandscapeEditorController()->getEditableLandscape();

	m_surface
		= QPixmap( QSize(
				landscape->getWidth() * Resources::Landscape::CellSize
			,	landscape->getHeight() * Resources::Landscape::CellSize ) );

	QPainter painter;
	painter.begin( &m_surface );
	painter.setRenderHint( QPainter::Antialiasing );

	for ( unsigned int i = 0; i < landscape->getWidth(); ++i )
	{
		for ( unsigned int j = 0; j < landscape->getHeight(); ++j )
		{
			Plugins::Core::LandscapeModel::SurfaceItems::Enum
				surfaceItem = landscape->getSurfaceItem( Plugins::Core::LandscapeModel::Point( i, j ) );

			QColor color;

			switch( surfaceItem )
			{
			case Plugins::Core::LandscapeModel::SurfaceItems::Grass:
				color.setRgb( 50, 200, 100 );
				break;
			case Plugins::Core::LandscapeModel::SurfaceItems::Sand:
				color.setRgb( 255, 200, 50 );
				break;
			case Plugins::Core::LandscapeModel::SurfaceItems::Snow:
				color.setRgb( 155, 255, 255 );
				break;
			case Plugins::Core::LandscapeModel::SurfaceItems::Wather:
				color.setRgb( 0, 120, 245 );
				break;
			default:
				assert( !"Unrecognized surface item" );
				break;
			}

			QBrush surfaceItemBrash( color );
			painter.fillRect(
					QRect(
							i * Resources::Landscape::CellSize
						,	j * Resources::Landscape::CellSize
						,	Resources::Landscape::CellSize
						,	Resources::Landscape::CellSize )
				, surfaceItemBrash );
		}
	}

	for ( unsigned int i = 0; i < landscape->getWidth(); ++i )
		painter.drawLine(
				i * Resources::Landscape::CellSize
			,	0
			,	i * Resources::Landscape::CellSize
			,	m_surface.size().height() );

	for ( unsigned int i = 0; i < landscape->getHeight(); ++i )
		painter.drawLine(
				0
			,	i * Resources::Landscape::CellSize
			,	m_surface.size().width()
			,	i * Resources::Landscape::CellSize );

} // LandscapeWidget::regenerateSurface


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
