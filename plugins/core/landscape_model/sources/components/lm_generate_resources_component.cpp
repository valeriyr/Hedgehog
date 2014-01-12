
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_generate_resources_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


GenerateResourcesComponent::GenerateResourcesComponent(
		Object& _object
	,	const GenerateResourcesComponentStaticData& _staticData
	)
	:	BaseComponent< IGenerateResourcesComponent >( _object )
	,	m_staticData( _staticData )
	,	m_enableGenerating( true )
{
} // GenerateResourcesComponent::GenerateResourcesComponent


/*---------------------------------------------------------------------------*/


GenerateResourcesComponent::~GenerateResourcesComponent()
{
} // GenerateResourcesComponent::~GenerateResourcesComponent


/*---------------------------------------------------------------------------*/


const GenerateResourcesComponentStaticData&
GenerateResourcesComponent::getStaticData() const
{
	return m_staticData;

} // GenerateResourcesComponent::getStaticData


/*---------------------------------------------------------------------------*/


bool
GenerateResourcesComponent::isGeneratingEnabled() const
{
	return m_enableGenerating;

} // GenerateResourcesComponent::isGeneratingEnabled


/*---------------------------------------------------------------------------*/


void
GenerateResourcesComponent::enableGenerating( const bool _enable )
{
	m_enableGenerating = _enable;

} // GenerateResourcesComponent::enableGenerating


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
