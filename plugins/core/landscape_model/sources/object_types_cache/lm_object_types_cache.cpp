
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
ObjectTypesCache::regObjectType(
		const QString& _name
	,	const unsigned int _maximumHealth
	,	const QSize& _objectSize
	,	const TerrainMapItem::MaskType _passability
	,	const unsigned int _movingSpeed )
{
	m_typesCollection.insert(
		std::make_pair(
				_name
			,	boost::intrusive_ptr< IObjectType >(
					new ObjectType( _name, _maximumHealth, _objectSize, _passability, _movingSpeed ) ) ) );

} // ObjectTypesCache::regObjectType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
