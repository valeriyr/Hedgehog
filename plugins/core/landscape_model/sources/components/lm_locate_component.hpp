
#ifndef __LM_LOCATE_COMPONENT_HPP__
#define __LM_LOCATE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_ilocate_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class LocateComponent
	:	public BaseComponent< ILocateComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LocateComponent(
			GameObject& _object
		,	const ILocateComponent::StaticData& _staticData
		,	const QPoint& _location );

	virtual ~LocateComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const ILocateComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Direction::Enum getDirection() const;

	/*virtual*/ void setDirection( const Direction::Enum _direction );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QRect getRect() const;

	/*virtual*/ const QPoint& getLocation() const;

	/*virtual*/ void setLocation( const QPoint& _location );

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isHidden() const;

	/*virtual*/ void setHidden( const bool _hidden );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILocateComponent::StaticData& m_staticData;

	QPoint m_location;

	Direction::Enum m_direction;

	bool m_isHidden;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LOCATE_COMPONENT_HPP__
