
#ifndef __LM_IUNITS_CACHE_HPP__
#define __LM_IUNITS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_UNITS_CACHE = 3;

/*---------------------------------------------------------------------------*/

struct IUnit;

/*---------------------------------------------------------------------------*/

struct IUnitsCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUnit >
		cloneUnit( const QString& _name ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void addUnit(
			const QString& _name
		,	const QString& _bundlePath
		,	const QRect& _rectInBundle ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IUNITS_CACHE_HPP__
