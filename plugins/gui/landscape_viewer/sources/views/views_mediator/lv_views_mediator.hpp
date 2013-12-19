
#ifndef __LV_VIEWS_MEDIATOR_HPP__
#define __LV_VIEWS_MEDIATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class ViewsMediator
	:	public QObject
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ViewsMediator();

	virtual ~ViewsMediator();

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void visibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

	void landscapeViewWasResized( const float _visibleWidth, const float _visibleHeight );

	void visibilityRectChangedPosition( const float _visibleWidth, const float _visibleHeight );

	void currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& _id );

	void currentObjectWasChanged( const QString& _name );

	void controlItemSelected();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_VIEWS_MEDIATOR_HPP__
