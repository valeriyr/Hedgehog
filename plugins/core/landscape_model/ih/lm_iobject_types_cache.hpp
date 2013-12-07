
#ifndef __LM_IOBJECT_TYPES_CACHE_HPP__
#define __LM_IOBJECT_TYPES_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_OBJECT_TYPES_CACHE = 3;

/*---------------------------------------------------------------------------*/

struct IObjectType;

/*---------------------------------------------------------------------------*/

struct IObjectTypesCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IObjectType > getObjectType( const QString& _name ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regObjectType(
			const QString& _name
		,	const const unsigned int _maximumHealth ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IOBJECT_TYPES_CACHE_HPP__
