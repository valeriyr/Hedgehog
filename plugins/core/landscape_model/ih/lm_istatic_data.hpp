
#ifndef __LM_ISTATIC_DATA_HPP__
#define __LM_ISTATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/components/lm_itrain_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"
#include "landscape_model/ih/components/lm_imove_component.hpp"
#include "landscape_model/ih/components/lm_igenerate_resources_component.hpp"
#include "landscape_model/ih/components/lm_ibuild_component.hpp"
#include "landscape_model/ih/components/lm_irepair_component.hpp"
#include "landscape_model/ih/components/lm_iresource_holder_component.hpp"
#include "landscape_model/ih/components/lm_iresource_source_component.hpp"
#include "landscape_model/ih/components/lm_iresource_storage_component.hpp"
#include "landscape_model/ih/components/lm_iplayer_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_STATIC_DATA = 2;

/*---------------------------------------------------------------------------*/

struct IStaticData
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct ObjectStaticData
	{
		boost::shared_ptr< ITrainComponent::StaticData > m_trainData;
		boost::shared_ptr< Tools::Core::Object > m_healthData;
		boost::shared_ptr< ILocateComponent::StaticData > m_locateData;
		boost::shared_ptr< Tools::Core::Object > m_selectionData;
		boost::shared_ptr< IMoveComponent::StaticData > m_moveData;
		boost::shared_ptr< IGenerateResourcesComponent::StaticData > m_generateResourcesData;
		boost::shared_ptr< Tools::Core::Object > m_attackData;
		boost::shared_ptr< IBuildComponent::StaticData > m_buildData;
		boost::shared_ptr< IRepairComponent::StaticData > m_repairData;
		boost::shared_ptr< IResourceHolderComponent::StaticData > m_resourceHolderData;
		boost::shared_ptr< IResourceSourceComponent::StaticData > m_resourceSourceData;
		boost::shared_ptr< IResourceStorageComponent::StaticData > m_resourceStorageData;
		boost::shared_ptr< IPlayerComponent::StaticData > m_playerData;
	};

/*---------------------------------------------------------------------------*/

	typedef std::map< QString, ObjectStaticData > StaticDataCollection;
	typedef StaticDataCollection::const_iterator StaticDataCollectionConstIterator;
	typedef StaticDataCollection::iterator StaticDataCollectionIterator;

	typedef std::map< QString, int > ResourcesCollection;
	typedef ResourcesCollection::const_iterator ResourcesCollectionConstIterator;
	typedef ResourcesCollection::iterator ResourcesCollectionIterator;

	typedef std::map< QString, QString > RacesCollection;
	typedef RacesCollection::const_iterator RacesCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual const ObjectStaticData getObjectStaticData( const QString& _name ) const = 0;

	virtual void fetchObjectsStaticData( StaticDataCollection& _collection ) const = 0;

	virtual void regObjectStaticData( const QString& _name, const ObjectStaticData& _data ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void regObjectCreator( const QString& _name, const QString& _creatorName ) = 0;

	virtual const QString& getObjectCreator( const QString& _name ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regResource( const QString& _name, const int _startupValue ) = 0;

	virtual void fetchResources( ResourcesCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regRace( const QString& _raceName, const QString& _startPointObjectName ) = 0;

	virtual void fetchRaces( RacesCollection& _collection ) const = 0;

	virtual QString getStartPointObjectName( const QString& _raceName ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISTATIC_DATA_HPP__
