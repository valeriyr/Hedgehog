
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
	,	m_resourceValue( 200 )
	,	m_objectInside( Object::ms_wrongId )
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


const Object::Id&
ResourceSourceComponent::getObjectInside() const
{
	return m_objectInside;

} // ResourceSourceComponent::getObjectInside


/*---------------------------------------------------------------------------*/


void
ResourceSourceComponent::setObjectInside( const Object::Id& _id )
{
	m_objectInside = _id;

} // ResourceSourceComponent::setObjectInside


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
