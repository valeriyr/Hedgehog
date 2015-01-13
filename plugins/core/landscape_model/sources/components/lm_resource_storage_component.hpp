
#ifndef __LM_RESOURCE_STORAGE_COMPONENT_HPP__
#define __LM_RESOURCE_STORAGE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_iresource_storage_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class ResourceStorageComponent
	:	public BaseComponent< IResourceStorageComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ResourceStorageComponent(
			GameObject& _object
		,	const IResourceStorageComponent::StaticData& _staticData );

	virtual ~ResourceStorageComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IResourceStorageComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IResourceStorageComponent::StaticData& m_staticData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_RESOURCE_STORAGE_COMPONENT_HPP__
