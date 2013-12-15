
#ifndef __LV_ILANDSCAPE_SCENE_STATE_HPP__
#define __LV_ILANDSCAPE_SCENE_STATE_HPP__


#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct ILandscapeSceneState
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent ) = 0;

	virtual void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent ) = 0;

	virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent ) = 0;

	virtual void onMousePossitionWasChanged( const QPointF& _point ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ILANDSCAPE_SCENE_STATE_HPP__
