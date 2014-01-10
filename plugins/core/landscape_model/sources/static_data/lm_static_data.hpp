
#ifndef __LM_STATIC_DATA_HPP__
#define __LM_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_istatic_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class StaticData
	:	public Tools::Core::BaseWrapper< IStaticData >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	StaticData();

	virtual ~StaticData();

/*---------------------------------------------------------------------------*/

	/*virtual*/ IStaticData::ObjectStaticData getObjectStaticData( const QString& _name ) const;

	/*virtual*/ void fetchObjectsStaticData( IStaticData::StaticDataCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regBuilderStaticData(
			const QString& _name
		,	boost::shared_ptr< const BuilderComponentStaticData > _data );

	/*virtual*/ void regHealthStaticData(
			const QString& _name
		,	boost::shared_ptr< const HealthComponentStaticData > _data );

	/*virtual*/ void regLocateStaticData(
			const QString& _name
		,	boost::shared_ptr< const LocateComponentStaticData > _data );

	/*virtual*/ void regSelectionStaticData(
			const QString& _name
		,	boost::shared_ptr< const SelectionComponentStaticData > _data );

	/*virtual*/ void regActionsStaticData(
			const QString& _name
		,	boost::shared_ptr< const ActionsComponentStaticData > _data );

	/*virtual*/ void regMoveStaticData(
			const QString& _name
		,	boost::shared_ptr< const MoveComponentStaticData > _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IStaticData::ObjectStaticData& ensureObjectInCollection( const QString& _name );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IStaticData::StaticDataCollection m_staticData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ÛTATIC_DATA_HPP__
