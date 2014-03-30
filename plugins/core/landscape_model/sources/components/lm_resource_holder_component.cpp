
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
	,	m_resourcesValue()
{
	Core::LandscapeModel::ResourcesData::ResourcesDataCollectionConstIterator
			begin = m_staticData.m_maxResourcesValue.m_data.begin()
		,	end = m_staticData.m_maxResourcesValue.m_data.end();

	for ( ; begin != end; ++begin )
	{
		m_resourcesValue.pushResource( begin->first, 0 );
	}

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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
