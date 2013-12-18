
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "containers/cn_matrix.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache;
struct IObjectTypesCache;

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< IEditableLandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape(
			const ISurfaceItemsCache& _surfaceItemsCache
		,	const IObjectTypesCache& _objectTypesCache );

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const;

	/*virtual*/ const TerrainMapData& getTerrainMapData( const QPoint& _point ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IUnit > getUnit( const QPoint& _point ) const;

	/*virtual*/ boost::intrusive_ptr< IUnit > getUnit( const IUnit::IdType& _id ) const;

	/*virtual*/ unsigned int getUnitsCount() const;

	/*virtual*/ void fetchUnits( ILandscape::UnitsCollection& _collection ) const;

	/*virtual*/ void fetchSelectedUnits( ILandscape::UnitsCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool canCreateObject(
			const QPoint& _position
		,	const QString& _objectName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSize(
			const unsigned int _width
		,	const unsigned int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSurfaceItem(
			const QPoint& _point
		,	const ISurfaceItem::IdType& _surfaceItemId );

/*---------------------------------------------------------------------------*/

	/*virtual*/ IUnit::IdType createObject(
			const QPoint& _position
		,	const QString& _objectName );

	/*virtual*/ void selectUnits( const QRect& _rect );

	/*virtual*/ void unselectUnits();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/
	
	const ISurfaceItemsCache& m_surfaceItemsCache;
	const IObjectTypesCache& m_objectTypesCache;

/*---------------------------------------------------------------------------*/

	ILandscape::UnitsCollection m_units;
	ILandscape::UnitsCollection m_selectedUnits;

	Tools::Core::Containers::Matrix< boost::intrusive_ptr< ISurfaceItem > > m_surfaceItems;
	Tools::Core::Containers::Matrix< TerrainMapData > m_terrainMap;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
