
#ifndef __LM_ISTATIC_DATA_HPP__
#define __LM_ISTATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/components/lm_builder_component_static_data.hpp"
#include "landscape_model/h/components/lm_health_component_static_data.hpp"
#include "landscape_model/h/components/lm_locate_component_static_data.hpp"
#include "landscape_model/h/components/lm_selection_component_static_data.hpp"
#include "landscape_model/h/components/lm_actions_component_static_data.hpp"
#include "landscape_model/h/components/lm_move_component_static_data.hpp"
#include "landscape_model/h/components/lm_generate_resources_component_static_data.hpp"

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
		boost::shared_ptr< BuilderComponentStaticData > m_builderData;
		boost::shared_ptr< HealthComponentStaticData > m_healthData;
		boost::shared_ptr< LocateComponentStaticData > m_locateData;
		boost::shared_ptr< SelectionComponentStaticData > m_selectionData;
		boost::shared_ptr< ActionsComponentStaticData > m_actionsData;
		boost::shared_ptr< MoveComponentStaticData > m_moveData;
		boost::shared_ptr< GenerateResourcesComponentStaticData > m_generateResourcesData;
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
