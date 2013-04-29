
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

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem >
		getSurfaceItem( const unsigned int _width, const unsigned int _height ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IUnit >
		getUnit( const unsigned int _width, const unsigned int _height ) const;

	/*virtual*/ std::pair< unsigned int, unsigned int >
		getUnitPosition( boost::intrusive_ptr< IUnit > _unit ) const;

	/*virtual*/ unsigned int getUnitsCount() const;

	/*virtual*/ ILandscape::UnitsIteratorPtr getUnitsIterator() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ int getTerrainMapValue( const unsigned int _width, const unsigned int _height ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSize(
			const unsigned int _width
		,	const unsigned int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSurfaceItem(
			const unsigned int _width
		,	const unsigned int _height
		,	boost::intrusive_ptr< ISurfaceItem > _surfaceItem );

	/*virtual*/ void setUnit(
			const unsigned int _width
		,	const unsigned int _height
		,	boost::intrusive_ptr< IUnit > _unit );

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

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
