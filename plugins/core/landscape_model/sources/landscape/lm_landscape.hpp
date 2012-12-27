
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< IEditableLandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape();

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ ILandscapeObject::Ptr
		getLadscapeObject( const unsigned int _width, const unsigned int _height ) const;

	/*virtual*/ SurfaceItems::Enum
		getSurfaceItem( const unsigned int _width, const unsigned int _height ) const;

	/*virtual*/ TerrainMapItems::Enum
		getTerrainMapItem( const unsigned int _width, const unsigned int _height ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSize(
			const unsigned int _width
		,	const unsigned int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSurfaceItem(
			const unsigned int _width
		,	const unsigned int _height
		,	const SurfaceItems::Enum _surfaceItem );

	/*virtual*/ void createTreeObject( const unsigned int _width, const unsigned int _height );

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

	unsigned int m_width;

	unsigned int m_height;

/*---------------------------------------------------------------------------*/

	SurfaceItems::Enum ** m_surfaceItems;

	TerrainMapItems::Enum ** m_terrainMap;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
