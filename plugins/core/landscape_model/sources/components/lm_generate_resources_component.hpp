
#ifndef __LM_GENERATE_RESOURCES_COMPONENT_HPP__
#define __LM_GENERATE_RESOURCES_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_igenerate_resources_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class GenerateResourcesComponent
	:	public BaseComponent< IGenerateResourcesComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GenerateResourcesComponent( Object& _object, const IGenerateResourcesComponent::StaticData& _staticData );

	virtual ~GenerateResourcesComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IGenerateResourcesComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isGeneratingEnabled() const;

	/*virtual*/ void enableGenerating( const bool _enable );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IGenerateResourcesComponent::StaticData& m_staticData;

	bool m_enableGenerating;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_GENERATE_RESOURCES_COMPONENT_HPP__
