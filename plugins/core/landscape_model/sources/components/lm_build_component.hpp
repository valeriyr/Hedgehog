
#ifndef __LM_BUILD_COMPONENT_HPP__
#define __LM_BUILD_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_ibuild_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class BuildComponent
	:	public BaseComponent< IBuildComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BuildComponent( Object& _object, const IBuildComponent::StaticData& _staticData );

	virtual ~BuildComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IBuildComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ IBuildComponent::Data& getBuildData();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IBuildComponent::StaticData& m_staticData;

	IBuildComponent::Data m_data;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILD_COMPONENT_HPP__
