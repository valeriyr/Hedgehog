
#ifndef __LM_RESOURCE_HOLDER_COMPONENT_HPP__
#define __LM_RESOURCE_HOLDER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_iresource_holder_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class ResourceHolderComponent
	:	public BaseComponent< IResourceHolderComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ResourceHolderComponent(
			Object& _object
		,	const IResourceHolderComponent::StaticData& _staticData );

	virtual ~ResourceHolderComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IResourceHolderComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IResourceHolderComponent::StaticData& m_staticData;

	int m_resourceValue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_RESOURCE_HOLDER_COMPONENT_HPP__
