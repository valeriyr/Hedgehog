
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_resource_source_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ResourceSourceComponent::ResourceSourceComponent(
		Object& _object
	,	const IResourceSourceComponent::StaticData& _staticData
	)
	:	BaseComponent< IResourceSourceComponent >( _object )
	,	m_staticData( _staticData )
	,	m_resourceValue( 20000 )
{
} // ResourceSourceComponent::ResourceSourceComponent


/*---------------------------------------------------------------------------*/


ResourceSourceComponent::~ResourceSourceComponent()
{
} // ResourceSourceComponent::~ResourceSourceComponent


/*---------------------------------------------------------------------------*/


const IResourceSourceComponent::StaticData&
ResourceSourceComponent::getStaticData() const
{
	return m_staticData;

} // ResourceSourceComponent::getStaticData


/*---------------------------------------------------------------------------*/


const int
ResourceSourceComponent::getResourceValue() const
{
	return m_resourceValue;

} // ResourceSourceComponent::getResourceValue


/*---------------------------------------------------------------------------*/


void
ResourceSourceComponent::setResourceValue( const int _value )
{
	m_resourceValue = std::max( 0 , _value );

} // ResourceSourceComponent::setResourceValue


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
