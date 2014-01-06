
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/static_data/lm_static_data.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


StaticData::StaticData()
	:	m_staticData()
{
} // StaticData::StaticData


/*---------------------------------------------------------------------------*/


StaticData::~StaticData()
{
} // StaticData::~StaticData


/*---------------------------------------------------------------------------*/


IStaticData::ObjectStaticData
StaticData::getStaticData( const QString& _name ) const
{
	IStaticData::StaticDataCollectionConstIterator iterator
		= m_staticData.find( _name );

	if ( iterator != m_staticData.end() )
		return iterator->second;

	return IStaticData::ObjectStaticData();

} // StaticData::getStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::fetchStaticData( IStaticData::StaticDataCollection& _collection ) const
{
	_collection = m_staticData;

} // StaticData::getStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regBuilderStaticData(
		const QString& _name
	,	boost::shared_ptr< const BuilderComponentStaticData > _data )
{
	IStaticData::ObjectStaticData& data = ensureObjectInCollection( _name );

	assert( !data.m_builderData );

	data.m_builderData = _data;

} // StaticData::regBuilderStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regHealthStaticData(
		const QString& _name
	,	boost::shared_ptr< const HealthComponentStaticData > _data )
{
	IStaticData::ObjectStaticData& data = ensureObjectInCollection( _name );

	assert( !data.m_healthData );

	data.m_healthData = _data;

} // StaticData::regHealthStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regLocateStaticData(
		const QString& _name
	,	boost::shared_ptr< const LocateComponentStaticData > _data )
{
	IStaticData::ObjectStaticData& data = ensureObjectInCollection( _name );

	assert( !data.m_locateData );

	data.m_locateData = _data;

} // StaticData::regLocateStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regSelectionStaticData(
		const QString& _name
	,	boost::shared_ptr< const SelectionComponentStaticData > _data )
{
	IStaticData::ObjectStaticData& data = ensureObjectInCollection( _name );

	assert( !data.m_selectionData );

	data.m_selectionData = _data;

} // StaticData::regSelectionStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regActionsStaticData(
		const QString& _name
	,	boost::shared_ptr< const ActionsComponentStaticData > _data )
{
	IStaticData::ObjectStaticData& data = ensureObjectInCollection( _name );

	assert( !data.m_actionsData );

	data.m_actionsData = _data;

} // StaticData::regActionsStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regMoveStaticData(
		const QString& _name
	,	boost::shared_ptr< const MoveComponentStaticData > _data )
{
	IStaticData::ObjectStaticData& data = ensureObjectInCollection( _name );

	assert( !data.m_moveData );
	assert( _data->m_movingSpeed > 0 );

	data.m_moveData = _data;

} // StaticData::regMoveStaticData


/*---------------------------------------------------------------------------*/


IStaticData::ObjectStaticData&
StaticData::ensureObjectInCollection( const QString& _name )
{
	IStaticData::StaticDataCollectionIterator iterator = m_staticData.find( _name );

	if ( iterator == m_staticData.end() )
		iterator = m_staticData.insert( std::make_pair( _name, IStaticData::ObjectStaticData() ) ).first;

	return iterator->second;

} // StaticData::ensureObjectInCollection


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
