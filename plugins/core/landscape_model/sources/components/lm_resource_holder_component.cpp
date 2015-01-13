
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_resource_holder_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ResourceHolderComponent::ResourceHolderComponent(
		GameObject& _object
	,	const IResourceHolderComponent::StaticData& _staticData
	)
	:	BaseComponent< IResourceHolderComponent >( _object )
	,	m_staticData( _staticData )
	,	m_resourcesValue()
{
	IResourceHolderComponent::StaticData::ResourcesDataCollectionIterator
			begin = m_staticData.m_resourcesData.begin()
		,	end = m_staticData.m_resourcesData.end();

	for ( ; begin != end; ++begin )
		m_resourcesValue.pushResource( begin->first, 0 );

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


ResourcesData&
ResourceHolderComponent::holdResources()
{
	return m_resourcesValue;

} // ResourceHolderComponent::holdResources


/*---------------------------------------------------------------------------*/


bool
ResourceHolderComponent::isFull( const QString& _resourceName ) const
{
	IResourceHolderComponent::StaticData::ResourcesDataCollectionIterator
		iterator = m_staticData.m_resourcesData.find( _resourceName );

	assert( m_resourcesValue.getResourceValue( _resourceName ) <= iterator->second.m_maxValue );

	return m_resourcesValue.getResourceValue( _resourceName ) == iterator->second.m_maxValue;

} // ResourceHolderComponent::isFull


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
