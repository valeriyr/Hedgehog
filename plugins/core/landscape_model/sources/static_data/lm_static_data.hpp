
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

	/*virtual*/ const IStaticData::ObjectStaticData getObjectStaticData( const QString& _name ) const;

	/*virtual*/ void fetchObjectsStaticData( IStaticData::StaticDataCollection& _collection ) const;

	/*virtual*/ void regObjectStaticData( const QString& _name, const ObjectStaticData& _data );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regObjectCreator( const QString& _name, const QString& _creatorName );

	/*virtual*/ const QString& getObjectCreator( const QString& _name ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regResource( const QString& _name, const int _startupValue );

	/*virtual*/ void fetchResources( ResourcesCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regRace( const QString& _raceName, const QString& _startPointObjectName );

	/*virtual*/ void fetchRaces( IStaticData::RacesCollection& _collection ) const;

	/*virtual*/ QString getStartPointObjectName( const QString& _raceName ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef std::map< QString, QString > ObjectCreatorsCollection;
	typedef ObjectCreatorsCollection::const_iterator ObjectCreatorsCollectionIterator;

/*---------------------------------------------------------------------------*/

	ObjectCreatorsCollection m_objectsCreators;

	IStaticData::StaticDataCollection m_staticData;

	IStaticData::ResourcesCollection m_resources;

	IStaticData::RacesCollection m_races;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_STATIC_DATA_HPP__
