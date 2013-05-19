
#ifndef __LM_IEDITABLE_LANDSCAPE_HPP__
#define __LM_IEDITABLE_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape.hpp"

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
			const Point& _point
		,	boost::intrusive_ptr< ISurfaceItem > _surfaceItem ) = 0;

	virtual void setUnit(
			const Point& _point
		,	boost::intrusive_ptr< IUnit > _unit ) = 0;

	virtual void setSelectedUnit( const Point& _point ) = 0;

	virtual void moveUnit( boost::intrusive_ptr< IUnit > _unit, const Point& _point ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IEDITABLE_LANDSCAPE_HPP__
