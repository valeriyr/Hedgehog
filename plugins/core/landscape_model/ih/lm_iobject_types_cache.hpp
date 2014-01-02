
#ifndef __LM_IOBJECT_TYPES_CACHE_HPP__
#define __LM_IOBJECT_TYPES_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/h/lm_terrain_map_data.hpp"

#include "landscape_model/ih/lm_iobject_type.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_OBJECT_TYPES_CACHE = 2;

/*---------------------------------------------------------------------------*/

struct IObjectTypesCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< boost::intrusive_ptr< IObjectType > >
		TypesCollection;
	typedef
		TypesCollection::const_iterator
		TypesCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IObjectType > getObjectType( const QString& _name ) const = 0;

	virtual void fetchTypes( TypesCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regObjectType(
			const QString& _name
		,	const unsigned int _maximumHealth
		,	const QSize& _size
		,	const TerrainMapItem::MaskType _passability
		,	const unsigned int _movingSpeed ) = 0;

	virtual void regObjectType(
			const QString& _name
		,	const unsigned int _maximumHealth
		,	const QSize& _size
		,	const TerrainMapItem::MaskType _passability
		,	const unsigned int _movingSpeed
		,	const IObjectType::ObjectToCreateDataCollection& _objectsToCreate ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IOBJECT_TYPES_CACHE_HPP__
