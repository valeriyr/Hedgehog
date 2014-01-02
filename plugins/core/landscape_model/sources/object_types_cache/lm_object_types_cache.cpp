
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/object_types_cache/lm_object_types_cache.hpp"

#include "landscape_model/sources/object_type/lm_object_type.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ObjectTypesCache::ObjectTypesCache()
	:	m_typesCollection()
{
} // ObjectTypesCache::ObjectTypesCache


/*---------------------------------------------------------------------------*/


ObjectTypesCache::~ObjectTypesCache()
{
} // ObjectTypesCache::~ObjectTypesCache


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IObjectType >
ObjectTypesCache::getObjectType( const QString& _name ) const
{
	TypesCollectionIterator iterator( m_typesCollection.find( _name ) );

	if ( iterator != m_typesCollection.end() )
		return iterator->second;

	return boost::intrusive_ptr< IObjectType >();

} // ObjectTypesCache::getObjectType


/*---------------------------------------------------------------------------*/


void
ObjectTypesCache::fetchTypes( IObjectTypesCache::TypesCollection& _collection ) const
{
	_collection.clear();

	TypesCollectionIterator
			begin = m_typesCollection.begin()
		,	end = m_typesCollection.end();

	for ( ; begin != end; ++begin )
	{
		_collection.push_back( begin->second );
	}

} // ObjectTypesCache::fetchTypes


/*---------------------------------------------------------------------------*/

void
ObjectTypesCache::regObjectType(
		const QString& _name
	,	const unsigned int _maximumHealth
	,	const QSize& _size
	,	const TerrainMapItem::MaskType _passability
	,	const unsigned int _movingSpeed )
{
	regObjectType( _name, _maximumHealth, _size, _passability, _movingSpeed, IObjectType::ObjectToCreateDataCollection() );

} // ObjectTypesCache::regObjectType


/*---------------------------------------------------------------------------*/


void
ObjectTypesCache::regObjectType(
		const QString& _name
	,	const unsigned int _maximumHealth
	,	const QSize& _size
	,	const TerrainMapItem::MaskType _passability
	,	const unsigned int _movingSpeed
	,	const IObjectType::ObjectToCreateDataCollection& _objectsToCreate )
{
	m_typesCollection.insert(
		std::make_pair(
				_name
			,	boost::intrusive_ptr< IObjectType >(
					new ObjectType( _name, _maximumHealth, _size, _passability, _movingSpeed, _objectsToCreate ) ) ) );

} // ObjectTypesCache::regObjectType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
