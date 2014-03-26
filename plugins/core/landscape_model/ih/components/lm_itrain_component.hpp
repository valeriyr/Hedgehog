
#ifndef __LM_ITRAIN_COMPONENT_HPP__
#define __LM_ITRAIN_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_resources_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ITrainComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
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

		typedef
			std::map< QString, boost::shared_ptr< const TrainData > >
			TrainDataCollection;
		typedef
			TrainDataCollection::const_iterator
			TrainDataCollectionIterator;

		StaticData()
			:	m_trainObjects()
		{}

		void pushTrainData( const QString _objectName, boost::shared_ptr< TrainData > _data )
		{
			m_trainObjects.insert( std::make_pair( _objectName, _data ) );
		}

		TrainDataCollection m_trainObjects;
	};

/*---------------------------------------------------------------------------*/

	struct Data
	{
		Data()
			:	m_trainProgress( 0.0f )
			,	m_trainingObjectName()
		{}

		void reset()
		{
			 m_trainProgress = 0.0f;
			 m_trainingObjectName.clear();
		}

		float m_trainProgress;

		QString m_trainingObjectName;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual Data& getTrainData() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ITRAIN_COMPONENT_HPP__
