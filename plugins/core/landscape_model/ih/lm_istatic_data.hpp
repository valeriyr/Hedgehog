
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
		boost::shared_ptr< const BuilderComponentStaticData > m_builderData;
		boost::shared_ptr< const HealthComponentStaticData > m_healthData;
		boost::shared_ptr< const LocateComponentStaticData > m_locateData;
		boost::shared_ptr< const SelectionComponentStaticData > m_selectionData;
		boost::shared_ptr< const ActionsComponentStaticData > m_actionsData;
		boost::shared_ptr< const MoveComponentStaticData > m_moveData;
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

/*---------------------------------------------------------------------------*/

	virtual ObjectStaticData getStaticData( const QString& _name ) const = 0;

	virtual void fetchStaticData( StaticDataCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regBuilderStaticData(
			const QString& _name
		,	boost::shared_ptr< const BuilderComponentStaticData > _data ) = 0;

	virtual void regHealthStaticData(
			const QString& _name
		,	boost::shared_ptr< const HealthComponentStaticData > _data ) = 0;

	virtual void regLocateStaticData(
			const QString& _name
		,	boost::shared_ptr< const LocateComponentStaticData > _data ) = 0;

	virtual void regSelectionStaticData(
			const QString& _name
		,	boost::shared_ptr< const SelectionComponentStaticData > _data ) = 0;

	virtual void regActionsStaticData(
			const QString& _name
		,	boost::shared_ptr< const ActionsComponentStaticData > _data ) = 0;

	virtual void regMoveStaticData(
			const QString& _name
		,	boost::shared_ptr< const MoveComponentStaticData > _data ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISTATIC_DATA_HPP__
