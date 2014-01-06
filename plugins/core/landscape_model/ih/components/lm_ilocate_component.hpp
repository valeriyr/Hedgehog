
#ifndef __LM_ILOCATE_COMPONENT_HPP__
#define __LM_ILOCATE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_locate_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILocateComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	virtual const LocateComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const Direction::Enum getDirection() const = 0;

	virtual void setDirection( const Direction::Enum _direction ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const QRect getRect() const = 0;

	virtual const QPoint& getLocation() const = 0;

	virtual void setLocation( const QPoint& _location ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILOCATE_COMPONENT_HPP__
