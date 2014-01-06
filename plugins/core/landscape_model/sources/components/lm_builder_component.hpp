
#ifndef __LM_BUILDER_COMPONENT_HPP__
#define __LM_BUILDER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_ibuilder_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class BuilderComponent
	:	public BaseComponent< IBuilderComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BuilderComponent( Object& _object, const BuilderComponentStaticData& _staticData );

	virtual ~BuilderComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const BuilderComponentStaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const BuilderComponentStaticData& m_staticData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILDER_COMPONENT_HPP__
