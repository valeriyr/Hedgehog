
#ifndef __LM_ISTATIC_DATA_HPP__
#define __LM_ISTATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/components/lm_itrain_component.hpp"
#include "landscape_model/ih/components/lm_ihealth_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iselection_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"
#include "landscape_model/ih/components/lm_imove_component.hpp"
#include "landscape_model/ih/components/lm_igenerate_resources_component.hpp"
#include "landscape_model/ih/components/lm_iattack_component.hpp"
#include "landscape_model/ih/components/lm_ibuild_component.hpp"
#include "landscape_model/ih/components/lm_irepair_component.hpp"
#include "landscape_model/ih/components/lm_iresource_holder_component.hpp"
#include "landscape_model/ih/components/lm_iresource_source_component.hpp"
#include "landscape_model/ih/components/lm_iresource_storage_component.hpp"

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
		boost::shared_ptr< IHealthComponent::StaticData > m_healthData;
		boost::shared_ptr< ILocateComponent::StaticData > m_locateData;
		boost::shared_ptr< ISelectionComponent::StaticData > m_selectionData;
		boost::shared_ptr< IMoveComponent::StaticData > m_moveData;
		boost::shared_ptr< IGenerateResourcesComponent::StaticData > m_generateResourcesData;
		boost::shared_ptr< IAttackComponent::StaticData > m_attackData;
		boost::shared_ptr< IBuildComponent::StaticData > m_buildData;
		boost::shared_ptr< IRepairComponent::StaticData > m_repairData;
		boost::shared_ptr< IResourceHolderComponent::StaticData > m_resourceHolderData;
		boost::shared_ptr< IResourceSourceComponent::StaticData > m_resourceSourceData;
		boost::shared_ptr< IResourceStorageComponent::StaticData > m_resourceStorageData;
	};

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, ObjectStaticData >
		StaticDataCollection;
	typedef
		StaticDataCollection::const_iterator
		StaticDataCollectionConstIterator;
	typedef
		StaticDataCollection::iterator
		StaticDataCollectionIterator;

	typedef
		std::set< QString >
		ResourcesCollection;
	typedef
		ResourcesCollection::const_iterator
		ResourcesCollectionConstIterator;
	typedef
		ResourcesCollection::iterator
		ResourcesCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual const ObjectStaticData getObjectStaticData( const QString& _name ) const = 0;

	virtual void fetchObjectsStaticData( StaticDataCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regObjectStaticData( const QString& _name, const ObjectStaticData& _data ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void regResource( const QString& _name ) = 0;

	virtual void fetchResources( ResourcesCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISTATIC_DATA_HPP__
