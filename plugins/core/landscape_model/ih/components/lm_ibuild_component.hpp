
#ifndef __LM_IBUILD_COMPONENT_HPP__
#define __LM_IBUILD_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_resources_data.hpp"
#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IBuildComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
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

		typedef
			std::map< QString, boost::shared_ptr< const BuildData > >
			BuildDataCollection;
		typedef
			BuildDataCollection::const_iterator
			BuildDataCollectionIterator;

		StaticData()
			:	m_buildDatas()
		{}

		void pushBuildData( const QString _objectName, boost::shared_ptr< BuildData > _data )
		{
			m_buildDatas.insert( std::make_pair( _objectName, _data ) );
		}

		BuildDataCollection m_buildDatas;
	};

/*---------------------------------------------------------------------------*/

	struct Data
	{
		typedef
			std::list< std::pair< QString, QPoint > >
			BuildObjectsQueue;
		typedef
			BuildObjectsQueue::const_iterator
			BuildObjectsQueueIterator;

		Data()
			:	m_buildProgress( 0.0f )
			,	m_objectId( Object::ms_wrongId )
			,	m_buildQueue()
		{}

		void clear()
		{
			 m_buildProgress = 0.0f;
			 m_objectId = Object::ms_wrongId;
			 m_buildQueue.clear();
		}

		void objectBuilt()
		{
			m_buildProgress = 0.0f;
			m_objectId = Object::ms_wrongId;
			m_buildQueue.pop_front();
		}

		float m_buildProgress;

		Object::Id m_objectId;

		BuildObjectsQueue m_buildQueue;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual Data& getBuildData() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IBUILD_COMPONENT_HPP__
