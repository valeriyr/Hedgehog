
#ifndef __LM_IRESOURCE_STORAGE_COMPONENT_HPP__
#define __LM_IRESOURCE_STORAGE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/lm_resources_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IResourceStorageComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		typedef
			std::set< QString >
			StoredResourcesCollection;
		typedef
			StoredResourcesCollection::const_iterator
			StoredResourcesCollectionIterator;

		StaticData()
			:	m_storedResources()
		{}

		void canStore( const QString& _resourceName )
		{
			m_storedResources.insert( _resourceName );
		}

		StoredResourcesCollection m_storedResources;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IRESOURCE_HOLDER_COMPONENT_HPP__
