
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_editor_widget.hpp"

#include "lv_landscape_editor_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeEditorWidget::LandscapeEditorWidget( QGraphicsScene* _scene, QWidget* _parent )
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

} // LandscapeEditorWidget::LandscapeEditorWidget


/*---------------------------------------------------------------------------*/


LandscapeEditorWidget::~LandscapeEditorWidget()
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

} // LandscapeEditorWidget::~LandscapeEditorWidget


/*---------------------------------------------------------------------------*/


void
LandscapeEditorWidget::wasResized()
{
	emit landscapeViewWasResized(
			scene()->width() == 0 ? 0.0f : static_cast< float >( width() ) / scene()->width()
		,	scene()->height() == 0 ? 0.0f : static_cast< float >( height() ) / scene()->height() );

} // LandscapeEditorWidget::wasResized


/*---------------------------------------------------------------------------*/


void
LandscapeEditorWidget::changeVisibleRect( const float _relPosotionByX, const float _relPosotionByY )
{
	verticalScrollBar()->setSliderPosition( verticalScrollBar()->maximum() * _relPosotionByY );
	horizontalScrollBar()->setSliderPosition( horizontalScrollBar()->maximum() * _relPosotionByX );

} // LandscapeEditorWidget::changeVisibleRect


/*---------------------------------------------------------------------------*/


void
LandscapeEditorWidget::onSliderMoved( int _value )
{
	emit visibleRectOfLandscapeViewWasChanged(
			horizontalScrollBar()->maximum() == 0 ? 0.0f : static_cast< float >( horizontalScrollBar()->value() ) / horizontalScrollBar()->maximum()
		,	verticalScrollBar()->maximum() == 0 ? 0.0f : static_cast< float >( verticalScrollBar()->value() ) / verticalScrollBar()->maximum() );

} // LandscapeEditorWidget::onSliderMoved


/*---------------------------------------------------------------------------*/


void
LandscapeEditorWidget::resizeEvent( QResizeEvent* _event )
{
	wasResized();

	QGraphicsView::resizeEvent( _event );

} // LandscapeEditorWidget::resizeEvent


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
