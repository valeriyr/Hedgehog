
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_view/le_landscape_view.hpp"

#include "le_landscape_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeView::LandscapeView( QGraphicsScene* _scene, QWidget* _parent )
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

} // LandscapeView::LandscapeView


/*---------------------------------------------------------------------------*/


LandscapeView::~LandscapeView()
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

} // LandscapeView::~LandscapeView


/*---------------------------------------------------------------------------*/


void
LandscapeView::onVisibleRectOnMinimapWasChanged( const float _relPosotionByX, const float _relPosotionByY )
{
	verticalScrollBar()->setSliderPosition( verticalScrollBar()->maximum() * _relPosotionByY );
	horizontalScrollBar()->setSliderPosition( horizontalScrollBar()->maximum() * _relPosotionByX );

} // LandscapeView::onVisibleRectOnMinimapWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeView::onSliderMoved( int _value )
{
	int v = verticalScrollBar()->value();
	int m = verticalScrollBar()->maximum();

	emit visibleRectOfLandscapeViewWasChanged(
			static_cast< float >( horizontalScrollBar()->value() ) / horizontalScrollBar()->maximum()
		,	static_cast< float >( verticalScrollBar()->value() ) / verticalScrollBar()->maximum() );

} // LandscapeView::onSliderMoved


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
