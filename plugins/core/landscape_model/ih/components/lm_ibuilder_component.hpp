
#ifndef __LM_IBUILDER_COMPONENT_HPP__
#define __LM_IBUILDER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_builder_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IBuilderComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	virtual const BuilderComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IBUILDER_COMPONENT_HPP__
