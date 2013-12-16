
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

	typedef
		std::vector< boost::intrusive_ptr< IUnit > >
		UnitsCollection;
	typedef
		UnitsCollection::const_iterator
		UnitsCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const = 0;

	virtual const TerrainMapData& getTerrainMapData( const QPoint& _point ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUnit > getUnit( const QPoint& _point ) const = 0;

	virtual unsigned int getUnitsCount() const = 0;

	virtual void fetchUnits( UnitsCollection& _collection ) const = 0;

	virtual void fetchSelectedUnits( UnitsCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual bool canCreateObject(
			const QPoint& _position
		,	const QString& _objectName ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
