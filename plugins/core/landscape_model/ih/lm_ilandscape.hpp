
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "iterators/it_simple_iterator.hpp"


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
		std::map< std::pair< unsigned int, unsigned int >, boost::intrusive_ptr< IUnit > >
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

	virtual boost::intrusive_ptr< ISurfaceItem >
		getSurfaceItem( const unsigned int _width, const unsigned int _height ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUnit >
		getUnit( const unsigned int _width, const unsigned int _height ) const = 0;

	virtual std::pair< unsigned int, unsigned int >
		getUnitPosition( boost::intrusive_ptr< IUnit > _unit ) const = 0;

	virtual unsigned int getUnitsCount() const = 0;

	virtual UnitsIteratorPtr getUnitsIterator() const = 0;

/*---------------------------------------------------------------------------*/

	virtual int getTerrainMapValue( const unsigned int _width, const unsigned int _height ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
