
#ifndef __LM_IGENERATE_RESOURCES_COMPONENT_HPP__
#define __LM_IGENERATE_RESOURCES_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_generate_resources_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IGenerateResourcesComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	virtual const GenerateResourcesComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual bool isGeneratingEnabled() const = 0;

	virtual void enableGenerating( const bool _enable ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IGENERATE_RESOURCES_COMPONENT_HPP__
