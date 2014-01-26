
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

	BuildComponent( Object& _object, const BuildComponentStaticData& _staticData );

	virtual ~BuildComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const BuildComponentStaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ IBuildComponent::BuildData& getBuildData();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const BuildComponentStaticData& m_staticData;

	IBuildComponent::BuildData m_buildData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILD_COMPONENT_HPP__
