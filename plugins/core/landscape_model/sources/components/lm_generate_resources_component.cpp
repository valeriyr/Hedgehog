
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_generate_resources_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


GenerateResourcesComponent::GenerateResourcesComponent(
		Object& _object
	,	const IGenerateResourcesComponent::StaticData& _staticData
	)
	:	BaseComponent< IGenerateResourcesComponent >( _object )
	,	m_staticData( _staticData )
{
} // GenerateResourcesComponent::GenerateResourcesComponent


/*---------------------------------------------------------------------------*/


GenerateResourcesComponent::~GenerateResourcesComponent()
{
} // GenerateResourcesComponent::~GenerateResourcesComponent


/*---------------------------------------------------------------------------*/


const IGenerateResourcesComponent::StaticData&
GenerateResourcesComponent::getStaticData() const
{
	return m_staticData;

} // GenerateResourcesComponent::getStaticData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
