
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_widget.hpp"

#include "lv_landscape_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeWidget::LandscapeWidget( QGraphicsScene* _scene, QWidget* _parent )
	:	QGraphicsView( _scene, _parent )
{
	QObject::connect(
			verticalScrollBar()
		,	SIGNAL( valueChanged( int ) )
		,	this
		,	SLOT( onSliderMoved( int ) ) );

	QObject::connect(
			horizontalScrollBar()
		,	SIGNAL( valueChanged( int ) )
		,	this
		,	SLOT( onSliderMoved( int ) ) );

} // LandscapeWidget::LandscapeWidget


/*---------------------------------------------------------------------------*/


LandscapeWidget::~LandscapeWidget()
{
	QObject::disconnect(
			verticalScrollBar()
		,	SIGNAL( valueChanged( int ) )
		,	this
		,	SLOT( onSliderMoved( int ) ) );

	QObject::disconnect(
			horizontalScrollBar()
		,	SIGNAL( valueChanged( int ) )
		,	this
		,	SLOT( onSliderMoved( int ) ) );

} // LandscapeWidget::~LandscapeWidget


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::wasResized()
{
	emit landscapeViewWasResized(
			scene()->width() == 0 ? 0.0f : static_cast< float >( width() ) / scene()->width()
		,	scene()->height() == 0 ? 0.0f : static_cast< float >( height() ) / scene()->height() );

} // LandscapeWidget::wasResized


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::onSliderMoved( int _value )
{
	emit visibleRectOfLandscapeViewWasChanged(
			horizontalScrollBar()->maximum() == 0 ? 0.0f : static_cast< float >( horizontalScrollBar()->value() ) / horizontalScrollBar()->maximum()
		,	verticalScrollBar()->maximum() == 0 ? 0.0f : static_cast< float >( verticalScrollBar()->value() ) / verticalScrollBar()->maximum() );

} // LandscapeWidget::onSliderMoved


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::onChangeVisibleRect( const float _relPosotionByX, const float _relPosotionByY )
{
	verticalScrollBar()->setSliderPosition( verticalScrollBar()->maximum() * _relPosotionByY );
	horizontalScrollBar()->setSliderPosition( horizontalScrollBar()->maximum() * _relPosotionByX );

} // LandscapeWidget::onChangeVisibleRect


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::resizeEvent( QResizeEvent* _event )
{
	QGraphicsView::resizeEvent( _event );

	wasResized();

} // LandscapeWidget::resizeEvent


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
