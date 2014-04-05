
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/static_data/lm_static_data.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


StaticData::StaticData()
	:	m_staticData()
	,	m_resources()
	,	m_races()
{
} // StaticData::StaticData


/*---------------------------------------------------------------------------*/


StaticData::~StaticData()
{
} // StaticData::~StaticData


/*---------------------------------------------------------------------------*/


const IStaticData::ObjectStaticData
StaticData::getObjectStaticData( const QString& _name ) const
{
	IStaticData::StaticDataCollectionConstIterator iterator
		= m_staticData.find( _name );

	if ( iterator != m_staticData.end() )
		return iterator->second;

	return IStaticData::ObjectStaticData();

} // StaticData::getObjectStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::fetchObjectsStaticData( IStaticData::StaticDataCollection& _collection ) const
{
	_collection = m_staticData;

} // StaticData::fetchObjectsStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regObjectStaticData( const QString& _name, const ObjectStaticData& _data )
{
	assert( m_staticData.find( _name ) == m_staticData.end() );

	m_staticData.insert( std::make_pair( _name, _data ) );

} // StaticData::regObjectStaticData


/*---------------------------------------------------------------------------*/


void
StaticData::regResource( const QString& _name )
{
	m_resources.insert( _name );

} // StaticData::regResource


/*---------------------------------------------------------------------------*/


void
StaticData::fetchResources( ResourcesCollection& _collection ) const
{
	_collection = m_resources;

} // StaticData::fetchResources


/*---------------------------------------------------------------------------*/


void
StaticData::regRace( const QString& _raceName, const QString& _startPointObjectName )
{
	m_races.insert( std::make_pair( _raceName, _startPointObjectName ) );

} // StaticData::regRace


/*---------------------------------------------------------------------------*/


QString
StaticData::getStartPointObjectName( const QString& _raceName ) const
{
	RacesCollectionIterator iterator = m_races.find( _raceName );

	return
				iterator != m_races.end()
			?	iterator->second
			:	QString();

} // StaticData::getStartPointObjectName


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
