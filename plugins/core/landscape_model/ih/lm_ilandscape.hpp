
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "iterators/it_simple_iterator.hpp"

#include "landscape_model/h/lm_point.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItem;
struct IUnit;

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Point, boost::intrusive_ptr< IUnit > >
		UnitsMap;
	typedef UnitsMap::const_iterator UnitsMapConstIterator;
	typedef UnitsMap::iterator UnitsMapIterator;

/*---------------------------------------------------------------------------*/

	typedef
		Tools::Core::SimpleIterator< UnitsMap, Tools::Core::SecondExtractor >
		UnitsIterator;

	typedef
		boost::shared_ptr< UnitsIterator >
		UnitsIteratorPtr;

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const Point& _point ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUnit > getUnit( const Point& _point ) const = 0;

	virtual Point getUnitPosition( boost::intrusive_ptr< IUnit > _unit ) const = 0;

	virtual unsigned int getUnitsCount() const = 0;

	virtual UnitsIteratorPtr getUnitsIterator() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUnit > getSelectedUnit() const = 0;

/*---------------------------------------------------------------------------*/

	virtual int getTerrainMapValue( const Point& _point ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
