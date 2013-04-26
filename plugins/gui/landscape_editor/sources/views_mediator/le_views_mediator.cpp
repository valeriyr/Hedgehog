
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views_mediator/le_views_mediator.hpp"

#include "le_views_mediator.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


ViewsMediator::ViewsMediator()
{
} // ViewsMediator::ViewsMediator


/*---------------------------------------------------------------------------*/


ViewsMediator::~ViewsMediator()
{
} // ViewsMediator::~ViewsMediator


/*---------------------------------------------------------------------------*/


void
ViewsMediator::onVisibleRectOnMinimapWasChanged( const float _relPosotionByX, const float _relPosotionByY )
{
	emit visibleRectOnMinimapWasChanged( _relPosotionByX, _relPosotionByY );

} // ViewsMediator::onVisibleRectOnMinimapWasChanged


/*---------------------------------------------------------------------------*/


void
ViewsMediator::onLandscapeViewWasResized( const float _visibleWidth, const float _visibleHeight )
{
	emit landscapeViewWasResized( _visibleWidth, _visibleHeight );

} // ViewsMediator::onLandscapeViewWasResized


/*---------------------------------------------------------------------------*/


void
ViewsMediator::onVisibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight )
{
	emit visibleRectOfLandscapeViewWasChanged( _visibleWidth, _visibleHeight );

} // ViewsMediator::onVisibleRectOfLandscapeViewWasChanged


/*---------------------------------------------------------------------------*/


void
ViewsMediator::onLandscapeWasChanged()
{
	emit landscapeWasChanged();

} // ViewsMediator::onLandscapeWasChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
