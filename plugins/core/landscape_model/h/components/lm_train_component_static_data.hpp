
#ifndef __LM_TRAIN_COMPONENT_STATIC_DATA_HPP__
#define __LM_TRAIN_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_resources_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct TrainData
{
	TrainData(
			const int _creationTime
		,	const ResourcesData& _resourcesData
		)
		:	m_creationTime( _creationTime )
		,	m_resourcesData( _resourcesData )
	{}

	const int m_creationTime;
	const ResourcesData m_resourcesData;
};


/*---------------------------------------------------------------------------*/


struct TrainComponentStaticData
{
	typedef
		std::map< QString, boost::shared_ptr< const TrainData > >
		TrainDataCollection;
	typedef
		TrainDataCollection::const_iterator
		TrainDataCollectionIterator;

	TrainComponentStaticData()
		:	m_buildObjects()
	{}

	void pushTrainData( const QString _objectName, boost::shared_ptr< TrainData > _data )
	{
		m_buildObjects.insert( std::make_pair( _objectName, _data ) );
	}

	TrainDataCollection m_buildObjects;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TRAIN_COMPONENT_STATIC_DATA_HPP__
