
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache;

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< IEditableLandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape( const ISurfaceItemsCache& _surfaceItemsCache );

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const Point& _point ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IUnit > getUnit( const Point& _point ) const;

	/*virtual*/ Point getUnitPosition( boost::intrusive_ptr< IUnit > _unit ) const;

	/*virtual*/ unsigned int getUnitsCount() const;

	/*virtual*/ ILandscape::UnitsIteratorPtr getUnitsIterator() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IUnit > getSelectedUnit() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ int getTerrainMapValue( const Point& _point ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSize(
			const unsigned int _width
		,	const unsigned int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSurfaceItem(
			const Point& _point
		,	boost::intrusive_ptr< ISurfaceItem > _surfaceItem );

	/*virtual*/ void setUnit(
			const Point& _point
		,	boost::intrusive_ptr< IUnit > _unit );

	/*virtual*/ void setSelectedUnit( const Point& _point );

	/*virtual*/ void moveUnit( boost::intrusive_ptr< IUnit > _unit, const Point& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	template< typename _TCollectionItem >
	void initCollection( _TCollectionItem**& _collection );

	template< typename _TCollection >
	void clearCollection( _TCollection& _collection );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/
	
	const ISurfaceItemsCache& m_surfaceItemsCache;

/*---------------------------------------------------------------------------*/

	unsigned int m_width;

	unsigned int m_height;

/*---------------------------------------------------------------------------*/

	ILandscape::UnitsMap m_units;

	ISurfaceItem *** m_surfaceItems;

	int ** m_terrainMap;

	boost::intrusive_ptr< IUnit > m_selectedUnit;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
