
#ifndef __LM_IEDITABLE_LANDSCAPE_HPP__
#define __LM_IEDITABLE_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEditableLandscape
	:	public ILandscape
{

/*---------------------------------------------------------------------------*/

	virtual void setSize(
			const unsigned int _width
		,	const unsigned int _height ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void setSurfaceItem(
			const QPoint& _point
		,	const ISurfaceItem::Id& _surfaceItemId ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void setEngagedWithGroungItem( const QPoint& _point, const bool _isEngaged ) = 0;

/*---------------------------------------------------------------------------*/

	virtual Object::UniqueId createObject(
			const QPoint& _location
		,	const QString& _objectName ) = 0;

	virtual void selectObjects( const QRect& _rect ) = 0;

	virtual void selectObject( const Object::UniqueId& _id ) = 0;

	virtual void unselectObjects() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IEDITABLE_LANDSCAPE_HPP__
