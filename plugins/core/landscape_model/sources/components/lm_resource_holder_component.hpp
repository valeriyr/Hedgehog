
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
			GameObject& _object
		,	const IResourceHolderComponent::StaticData& _staticData );

	virtual ~ResourceHolderComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IResourceHolderComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ ResourcesData& holdResources();

	/*virtual*/ bool isFull( const QString& _resourceName ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IResourceHolderComponent::StaticData& m_staticData;

	ResourcesData m_resourcesValue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_RESOURCE_HOLDER_COMPONENT_HPP__
