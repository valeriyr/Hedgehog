
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
	regenerateSurface();

	setFixedSize( m_surface.size() );

	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surface );

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
	/*QPainter painter;
	painter.begin( this );
	painter.drawPixmap( _event->rect(), m_surface.copy( _event->rect() ) );*/

	QGLWidget::paintEvent( _event );

	/*Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_environment.getLandscapeEditorController()->getEditableLandscape();

	if ( landscape )
	{
		QPainter painter;
		painter.begin( this );
		// painter.setRenderHint( QPainter::Antialiasing );
		painter.drawPixmap( 0, 0, m_surface );
	}
	else
	{
		QGLWidget::paintEvent( _event );
	}*/

    /*QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

	QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    QBrush background = QBrush(QColor(64, 32, 64));
    QBrush circleBrush = QBrush(gradient);
    QPen circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    QPen textPen = QPen(Qt::white);
    QFont textFont;
	textFont.setPixelSize(50);


    painter.fillRect(event->rect(), background);
    painter.translate(100, 100);

    painter.save();
    painter.setBrush(circleBrush);
    painter.setPen(circlePen);
	elapsed = ( elapsed + 100 ) % 1000;
    painter.rotate( elapsed * 0.030);

    qreal r = elapsed/1000.0;
    int n = 30;
    for (int i = 0; i < n; ++i) {
        painter.rotate(30);
        qreal radius = 0 + 120.0*((i+r)/n);
        qreal circleRadius = 1 + ((i+r)/n)*20;
        painter.drawEllipse(QRectF(radius, -circleRadius,
                                    circleRadius*2, circleRadius*2));
    }
    painter.restore();

    painter.setPen(textPen);
    painter.setFont(textFont);
    painter.drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, "Qt");

    painter.end();*/

} // LandscapeWidget::paintEvent


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
			case Plugins::Core::LandscapeModel::SurfaceItems::Ground:
				color.setRgb( 180, 140, 0 );
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
