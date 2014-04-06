
#ifndef __LM_RESOURCE_SOURCE_COMPONENT_HPP__
#define __LM_RESOURCE_SOURCE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_iresource_source_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class ResourceSourceComponent
	:	public BaseComponent< IResourceSourceComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ResourceSourceComponent(
			Object& _object
		,	const IResourceSourceComponent::StaticData& _staticData );

	virtual ~ResourceSourceComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IResourceSourceComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const int getResourceValue() const;

	/*virtual*/ void setResourceValue( const int _value );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Object::Id& getObjectInside() const;

	/*virtual*/ void setObjectInside( const Object::Id& _id );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IResourceSourceComponent::StaticData& m_staticData;

	int m_resourceValue;

	Object::Id m_objectInside;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_RESOURCE_SOURCE_COMPONENT_HPP__
