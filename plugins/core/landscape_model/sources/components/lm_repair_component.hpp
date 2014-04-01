
#ifndef __LM_REPAIR_COMPONENT_HPP__
#define __LM_REPAIR_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_irepair_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class RepairComponent
	:	public BaseComponent< IRepairComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	RepairComponent( Object& _object, const IRepairComponent::StaticData& _staticData );

	virtual ~RepairComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IRepairComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< Object > getTargetObject() const;

	/*virtual*/ void setTargetObject( boost::shared_ptr< Object > _object );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IRepairComponent::StaticData& m_staticData;

	boost::shared_ptr< Object > m_targetObject;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_REPAIR_COMPONENT_HPP__
