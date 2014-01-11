
#ifndef __LM_LANDSCAPE_HPP__
#define __LM_LANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape.hpp"

#include "containers/cn_matrix.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache;
struct IStaticData;

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< ILandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape(
			const ISurfaceItemsCache& _surfaceItemsCache
		,	const IStaticData& _staticData );

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ unsigned int getWidth() const;

	/*virtual*/ unsigned int getHeight() const;

	/*virtual*/ void setSize(
			const unsigned int _width
		,	const unsigned int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const;

	/*virtual*/ void setSurfaceItem(
			const QPoint& _point
		,	const ISurfaceItem::Id& _surfaceItemId );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const TerrainMapData& getTerrainMapData( const QPoint& _point ) const;

	/*virtual*/ void setEngagedWithGroungItem( const QPoint& _point, const bool _isEngaged );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< Object > getObject( const QPoint& _point ) const;

	/*virtual*/ boost::shared_ptr< Object > getObject( const Object::UniqueId& _id ) const;

	/*virtual*/ unsigned int getObjectsCount() const;

	/*virtual*/ void fetchObjects( ILandscape::ObjectsCollection& _collection ) const;

	/*virtual*/ void fetchSelectedObjects( ILandscape::ObjectsCollection& _collection ) const;

	/*virtual*/ Object::UniqueId createObject(
			const QPoint& _location
		,	const QString& _objectName );

	/*virtual*/ void selectObjects( const QRect& _rect );

	/*virtual*/ void selectObject( const Object::UniqueId& _id );

	/*virtual*/ void unselectObjects();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool canObjectBePlaced(
			const QPoint& _location
		,	const LocateComponentStaticData& _data ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/
	
	const ISurfaceItemsCache& m_surfaceItemsCache;
	const IStaticData& m_staticData;

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
