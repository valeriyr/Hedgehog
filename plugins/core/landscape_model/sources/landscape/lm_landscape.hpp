
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

	/*virtual*/ boost::intrusive_ptr< IObject > getObject( const QPoint& _point ) const;

	/*virtual*/ boost::intrusive_ptr< IObject > getObject( const IObject::IdType& _id ) const;

	/*virtual*/ unsigned int getObjectsCount() const;

	/*virtual*/ void fetchObjects( ILandscape::ObjectsCollection& _collection ) const;

	/*virtual*/ void fetchSelectedObjects( ILandscape::ObjectsCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool canObjectBePlaced(
			const QPoint& _position
		,	boost::intrusive_ptr< IObjectType > _objectType ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSize(
			const unsigned int _width
		,	const unsigned int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setSurfaceItem(
			const QPoint& _point
		,	const ISurfaceItem::IdType& _surfaceItemId );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setEngagedWithGroungItem( const QPoint& _point, const bool _isEngaged );

/*---------------------------------------------------------------------------*/

	/*virtual*/ IObject::IdType createObject(
			const QPoint& _position
		,	const QString& _objectName );

	/*virtual*/ void selectObjects( const QRect& _rect );

	/*virtual*/ void selectObject( const IObject::IdType& _id );

	/*virtual*/ void unselectObjects();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/
	
	const ISurfaceItemsCache& m_surfaceItemsCache;
	const IObjectTypesCache& m_objectTypesCache;

/*---------------------------------------------------------------------------*/

	ILandscape::ObjectsCollection m_objects;
	ILandscape::ObjectsCollection m_selectedObjects;

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
