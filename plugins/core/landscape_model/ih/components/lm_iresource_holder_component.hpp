
#ifndef __LM_IRESOURCE_HOLDER_COMPONENT_HPP__
#define __LM_IRESOURCE_HOLDER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/lm_resources_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IResourceHolderComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		struct ResourceData
		{
			ResourceData(
					const int _maxValue
				,	const int _collectTime
				)
				:	m_maxValue( _maxValue )
				,	m_collectTime( _collectTime )
			{}

			const int m_maxValue;
			const int m_collectTime;
		};

		typedef
			std::map< QString, ResourceData >
			ResourcesDataCollection;
		typedef
			ResourcesDataCollection::const_iterator
			ResourcesDataCollectionIterator;

		StaticData()
			:	m_resourcesData()
		{}

		void hold( const QString& _resourceName, const int _maxValue, const int _collectTime )
		{
			ResourcesDataCollectionIterator iterator = m_resourcesData.find( _resourceName );

			if ( iterator == m_resourcesData.end() )
			{
				m_resourcesData.insert( std::make_pair( _resourceName, ResourceData( _maxValue, _collectTime ) ) );
			}
		}

		const ResourceData& getHoldData( const QString& _resourceName ) const
		{
			ResourcesDataCollectionIterator iterator = m_resourcesData.find( _resourceName );

			assert( iterator != m_resourcesData.end() );

			return iterator->second;
		}

		ResourcesDataCollection m_resourcesData;
		
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual ResourcesData& holdResources() = 0;

	virtual bool isFull( const QString& _resourceName ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IRESOURCE_HOLDER_COMPONENT_HPP__
