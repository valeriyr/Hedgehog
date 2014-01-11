
#ifndef __LM_MOVE_COMPONENT_HPP__
#define __LM_MOVE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_imove_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class MoveComponent
	:	public BaseComponent< IMoveComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MoveComponent(
			Object& _object
		,	const MoveComponentStaticData& _staticData );

	virtual ~MoveComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const MoveComponentStaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ IMoveComponent::MovingData& getMovingData();

	/*virtual*/ void setPath( const IPathFinder::PointsCollection& _collection );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const MoveComponentStaticData& m_staticData;

	IMoveComponent::MovingData m_movingData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MOVE_COMPONENT_HPP__