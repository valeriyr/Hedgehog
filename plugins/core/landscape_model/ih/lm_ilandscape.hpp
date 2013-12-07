
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_terrain_map_data.hpp"

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

	struct UnitData
	{
		boost::intrusive_ptr< IUnit > m_unit;
		QRect m_rect;
	};

	typedef
		std::vector< UnitData >
		UnitsDataCollection;
	typedef
		UnitsDataCollection::const_iterator
		UnitsDataCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const = 0;

	virtual TerrainMapData getTerrainMapData( const QPoint& _point ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUnit > getUnit( const QPoint& _point ) const = 0;

	virtual unsigned int getUnitsCount() const = 0;

	virtual void fetchUnits( UnitsDataCollection& _collection ) const = 0;

	virtual void fetchSelectedUnits( UnitsDataCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
