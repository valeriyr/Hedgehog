
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_resource_holder_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ResourceHolderComponent::ResourceHolderComponent(
		Object& _object
	,	const IResourceHolderComponent::StaticData& _staticData
	)
	:	BaseComponent< IResourceHolderComponent >( _object )
	,	m_staticData( _staticData )
	,	m_resourceValue( 20000 )
{
} // ResourceHolderComponent::ResourceHolderComponent


/*---------------------------------------------------------------------------*/


ResourceHolderComponent::~ResourceHolderComponent()
{
} // ResourceHolderComponent::~ResourceHolderComponent


/*---------------------------------------------------------------------------*/


const IResourceHolderComponent::StaticData&
ResourceHolderComponent::getStaticData() const
{
	return m_staticData;

} // ResourceHolderComponent::getStaticData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
