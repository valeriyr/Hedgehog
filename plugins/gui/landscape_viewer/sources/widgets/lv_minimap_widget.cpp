
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_minimap_widget.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_iunit.hpp"

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
	,	m_landscape()
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
MinimapWidget::landscapeWasOpened(
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscape > _landscape )
{
	m_landscape = _landscape;

	onUpdateView();

} // MinimapWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
MinimapWidget::landscapeWasClosed()
{
	m_surfaceLayer.fill(Qt::white);
	m_objectsLayer.fill(Qt::transparent);

	m_visibleArea = QRect();

	m_landscape.reset();

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
MinimapWidget::onUpdateView()
{
	if ( m_landscape )
	{
		renderSurface( *m_landscape );
		renderObjects( *m_landscape );

		update();
	}

} // MinimapWidget::onUpdateView


/*---------------------------------------------------------------------------*/


void
MinimapWidget::paintEvent( QPaintEvent* _event )
{
	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surfaceLayer );
	painter.drawPixmap( 0, 0, m_objectsLayer );

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

	for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( unsigned int j = 0; j < _landscape.getHeight(); ++j )
		{
			boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
				surfaceItem = _landscape.getSurfaceItem( Plugins::Core::LandscapeModel::Point( i, j ) );

			painter.drawPixmap(
				QRect(
						i * Resources::Landscape::CellSize
					,	j * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize )
					,	m_environment.getPixmap( surfaceItem->getBundlePath(), surfaceItem->getRectInBundle() ) );
		}
	}

	m_surfaceLayer = surfaceLayer.scaled( ms_fixedWidgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

} // MinimapWidget::renderSurface


/*---------------------------------------------------------------------------*/


void
MinimapWidget::renderObjects( const Core::LandscapeModel::ILandscape& _landscape )
{
	QPixmap objectsLayer
		= QPixmap( QSize(
				_landscape.getWidth() * Resources::Landscape::CellSize
			,	_landscape.getHeight() * Resources::Landscape::CellSize ) );

	objectsLayer.fill( Qt::transparent );

	QPainter painter;
	painter.begin( &objectsLayer );
	painter.setRenderHint( QPainter::Antialiasing );

	Plugins::Core::LandscapeModel::ILandscape::UnitsIteratorPtr
		unitsIterator = _landscape.getUnitsIterator();

	while ( unitsIterator->isValid() )
	{
		Plugins::Core::LandscapeModel::Point position = _landscape.getUnitPosition( unitsIterator->current() );

		qreal posByX = position.m_x * Resources::Landscape::CellSize;
		qreal posByY = position.m_y * Resources::Landscape::CellSize;

		if ( static_cast< unsigned int >( unitsIterator->current()->getRectInBundle().width() ) > Resources::Landscape::CellSize )
		{
			posByX -= ( unitsIterator->current()->getRectInBundle().width() - Resources::Landscape::CellSize ) / 2;
		}

		if ( static_cast< unsigned int >( unitsIterator->current()->getRectInBundle().height() ) > Resources::Landscape::CellSize )
		{
			posByY -= ( unitsIterator->current()->getRectInBundle().height() - Resources::Landscape::CellSize ) / 2;
		}

		painter.drawPixmap(
			QRect(
					posByX
				,	posByY
				,	unitsIterator->current()->getRectInBundle().width()
				,	unitsIterator->current()->getRectInBundle().height() )
				,	m_environment.getPixmap( unitsIterator->current()->getBundlePath(), unitsIterator->current()->getRectInBundle() ) );

		unitsIterator->next();
	}

	m_objectsLayer = objectsLayer.scaled( ms_fixedWidgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

} // MinimapWidget::renderObjects


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
