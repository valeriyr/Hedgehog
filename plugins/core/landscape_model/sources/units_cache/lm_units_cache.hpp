
#ifndef __LM_UNITS_CACHE_HPP__
#define __LM_UNITS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iunits_cache.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct UnitsCache
	:	public Tools::Core::BaseWrapper< IUnitsCache >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	UnitsCache();

	virtual ~UnitsCache();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IUnit >
		cloneUnit( const QString& _name ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addUnit(
			const QString& _name
		,	const QString& _bundlePath
		,	const QRect& _rectInBundle );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, boost::intrusive_ptr< IUnit > >
		UnitsCollection;
	typedef
		UnitsCollection::const_iterator
		UnitsCollectionIterator;

/*---------------------------------------------------------------------------*/

	UnitsCollection m_unitsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_UNITS_CACHE_HPP__
