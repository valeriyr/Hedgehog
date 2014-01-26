
#ifndef __LM_BUILD_COMPONENT_STATIC_DATA_HPP__
#define __LM_BUILD_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_resources_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct BuildData
{
	BuildData(
			const int _buildTime
		,	const ResourcesData& _resourcesData
		)
		:	m_buildTime( _buildTime )
		,	m_resourcesData( _resourcesData )
	{}

	const int m_buildTime;
	const ResourcesData m_resourcesData;
};

/*---------------------------------------------------------------------------*/

struct BuildComponentStaticData
{
	typedef
		std::map< QString, boost::shared_ptr< const BuildData > >
		BuildDataCollection;
	typedef
		BuildDataCollection::const_iterator
		BuildDataCollectionIterator;

	BuildComponentStaticData()
		:	m_buildDatas()
	{}

	void pushBuildData( const QString _objectName, boost::shared_ptr< BuildData > _data )
	{
		m_buildDatas.insert( std::make_pair( _objectName, _data ) );
	}

	BuildDataCollection m_buildDatas;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILD_COMPONENT_STATIC_DATA_HPP__
