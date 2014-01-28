
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_terrain_map_data.hpp"
#include "landscape_model/h/lm_object.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct LocateComponentStaticData;

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< boost::shared_ptr< Object > >
		ObjectsCollection;
	typedef
		ObjectsCollection::const_iterator
		ObjectsCollectionIterator;
	typedef
		ObjectsCollection::const_iterator
		ObjectsCollectionConstIterator;

/*---------------------------------------------------------------------------*/

	virtual int getWidth() const = 0;

	virtual int getHeight() const = 0;

	virtual void setSize( const int _width, const int _height ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const = 0;

	virtual void setSurfaceItem(
			const QPoint& _point
		,	const ISurfaceItem::Id& _surfaceItemId ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const TerrainMapData& getTerrainMapData( const QPoint& _point ) const = 0;

	virtual void setEngaged( const QPoint& _point, const Emplacement::Enum _emplacement, const bool _isEngaged ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getObject( const QPoint& _point ) const = 0;

	virtual boost::shared_ptr< Object > getObject( const Object::UniqueId& _id ) const = 0;

	virtual int getObjectsCount() const = 0;

	virtual void fetchObjects( ObjectsCollection& _collection ) const = 0;

	virtual void fetchSelectedObjects( ObjectsCollection& _collection ) const = 0;

	virtual Object::UniqueId createObject( const QPoint& _location, const QString& _objectName ) = 0;

	virtual Object::UniqueId createObjectForBuilding( const QPoint& _location, const QString& _objectName ) = 0;

	virtual boost::shared_ptr< Object > removeObject( const Object::UniqueId& _id ) = 0;

	virtual void addObject( boost::shared_ptr< Object > _object ) = 0;

	virtual void selectObjects( const QRect& _rect ) = 0;

	virtual void selectObject( const Object::UniqueId& _id ) = 0;

	virtual void unselectObjects() = 0;

/*---------------------------------------------------------------------------*/

	virtual bool canObjectBePlaced(
			const QPoint& _location
		,	const LocateComponentStaticData& _data ) const = 0;

	virtual QPoint getNearestLocation( const Object& _nearestFrom, const QString& _forObject ) const = 0;

	virtual bool isLocationInLandscape( const QPoint& _location ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
