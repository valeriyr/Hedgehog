
#ifndef __LM_OBJECT_TYPES_CACHE_HPP__
#define __LM_OBJECT_TYPES_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iobject_types_cache.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ObjectTypesCache
	:	public Tools::Core::BaseWrapper< IObjectTypesCache >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ObjectTypesCache();

	virtual ~ObjectTypesCache();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IObjectType >
		getObjectType( const QString& _name ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regObjectType(
			const QString& _name
		,	const unsigned int _maximumHealth
		,	const QSize& _objectSize
		,	const TerrainMapItem::MaskType _passability
		,	const unsigned int _movingSpeed );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, boost::intrusive_ptr< IObjectType > >
		TypesCollection;
	typedef
		TypesCollection::const_iterator
		TypesCollectionIterator;

/*---------------------------------------------------------------------------*/

	TypesCollection m_typesCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_OBJECT_TYPES_CACHE_HPP__
