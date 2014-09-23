
#ifndef __LM_IBUILD_COMPONENT_HPP__
#define __LM_IBUILD_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_constants.hpp"
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
					const TickType _ticksCount
				,	const ResourcesData& _resourcesData
				)
				:	m_ticksCount( _ticksCount )
				,	m_resourcesData( _resourcesData )
			{}

			const TickType m_ticksCount;
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
		Data()
			:	m_objectName()
			,	m_atRect()
			,	m_buildProgress( 0 )
			,	m_objectId( Tools::Core::Generators::IGenerator::ms_wrongId )
		{}

		void reset()
		{
			m_objectName.clear();
			m_atRect = QRect();
			m_buildProgress = 0;
			m_objectId = Tools::Core::Generators::IGenerator::ms_wrongId;
		}

		QString m_objectName;
		QRect m_atRect;

		TickType m_buildProgress;

		Tools::Core::Generators::IGenerator::IdType m_objectId;
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
