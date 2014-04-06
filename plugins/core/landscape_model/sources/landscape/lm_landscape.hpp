
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
struct IObjectCreator;

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< ILandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape(
			const ISurfaceItemsCache& _surfaceItemsCache
		,	const IStaticData& _staticData
		,	IObjectCreator& _objectCreator );

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ int getWidth() const;

	/*virtual*/ int getHeight() const;

	/*virtual*/ void setSize( const int _width, const int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setStartPoint( const IPlayer::Id& _playerId, const QPoint& _point );

	/*virtual*/ QPoint getStartPoint( const IPlayer::Id& _playerId ) const;

	/*virtual*/ ILandscape::StartPointsIterator getStartPointsIterator() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const;

	/*virtual*/ void setSurfaceItem(
			const QPoint& _point
		,	const ISurfaceItem::Id& _surfaceItemId );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const TerrainMapData& getTerrainMapData( const QPoint& _point ) const;

	/*virtual*/ void setEngaged( const QPoint& _point, const Emplacement::Enum _emplacement, const bool _isEngaged );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< Object > getObject( const QPoint& _point ) const;

	/*virtual*/ boost::shared_ptr< Object > getObject( const Object::Id& _id ) const;

	/*virtual*/ int getObjectsCount() const;

	/*virtual*/ void fetchObjects( ILandscape::ObjectsCollection& _collection ) const;

	/*virtual*/ void fetchSelectedObjects( ILandscape::ObjectsCollection& _collection ) const;

	/*virtual*/ Object::Id createObject( const QString& _objectName, const QPoint& _location, const IPlayer::Id& _playerId );

	/*virtual*/ Object::Id createObjectForBuilding( const QString& _objectName, const QPoint& _location, const IPlayer::Id& _playerId );

	/*virtual*/ boost::shared_ptr< Object > hideObject( const Object::Id& _id );

	/*virtual*/ void showObject( boost::shared_ptr< Object > _object );

	/*virtual*/ void selectObjects( const QRect& _rect );

	/*virtual*/ void selectObject( const Object::Id& _id );

	/*virtual*/ void unselectObjects();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool canObjectBePlaced(
			const QPoint& _location
		,	const QString& _objectName ) const;

	/*virtual*/ QPoint getNearestLocation( const Object& _nearestFrom, const QString& _forObject ) const;

	/*virtual*/ bool isLocationInLandscape( const QPoint& _location ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/
	
	const ISurfaceItemsCache& m_surfaceItemsCache;
	const IStaticData& m_staticData;
	IObjectCreator& m_objectCreator;

/*---------------------------------------------------------------------------*/

	ILandscape::ObjectsCollection m_objects;
	ILandscape::ObjectsCollection m_selectedObjects;

	Tools::Core::Containers::Matrix< boost::intrusive_ptr< ISurfaceItem > > m_surfaceItems;
	Tools::Core::Containers::Matrix< TerrainMapData > m_terrainMap;

/*---------------------------------------------------------------------------*/

	typedef
		std::map< IPlayer::Id, QPoint >
		StartsPointsCollection;
	typedef
		StartsPointsCollection::iterator
		StartsPointsCollectionIterator;
	typedef
		StartsPointsCollection::const_iterator
		StartsPointsCollectionConstIterator;

	StartsPointsCollection m_startPoints;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
