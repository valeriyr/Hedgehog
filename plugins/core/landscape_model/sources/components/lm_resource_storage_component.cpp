
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_resource_storage_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ResourceStorageComponent::ResourceStorageComponent(
		GameObject& _object
	,	const IResourceStorageComponent::StaticData& _staticData
	)
	:	BaseComponent< IResourceStorageComponent >( _object )
	,	m_staticData( _staticData )
{
} // ResourceStorageComponent::ResourceStorageComponent


/*---------------------------------------------------------------------------*/


ResourceStorageComponent::~ResourceStorageComponent()
{
} // ResourceStorageComponent::~ResourceStorageComponent


/*---------------------------------------------------------------------------*/


const IResourceStorageComponent::StaticData&
ResourceStorageComponent::getStaticData() const
{
	return m_staticData;

} // ResourceStorageComponent::getStaticData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
