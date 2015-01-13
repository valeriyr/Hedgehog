
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_resource_source_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ResourceSourceComponent::ResourceSourceComponent(
		GameObject& _object
	,	const IResourceSourceComponent::StaticData& _staticData
	)
	:	BaseComponent< IResourceSourceComponent >( _object )
	,	m_staticData( _staticData )
	,	m_resourceValue( 20000 )
	,	m_objectInside( Tools::Core::Generators::IGenerator::ms_wrongId )
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


const Tools::Core::Generators::IGenerator::IdType&
ResourceSourceComponent::getObjectInside() const
{
	return m_objectInside;

} // ResourceSourceComponent::getObjectInside


/*---------------------------------------------------------------------------*/


void
ResourceSourceComponent::setObjectInside( const Tools::Core::Generators::IGenerator::IdType& _id )
{
	m_objectInside = _id;

} // ResourceSourceComponent::setObjectInside


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
