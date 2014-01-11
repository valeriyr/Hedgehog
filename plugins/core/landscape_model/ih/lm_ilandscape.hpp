
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

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

	virtual void setSize(
			const unsigned int _width
		,	const unsigned int _height ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const = 0;

	virtual void setSurfaceItem(
			const QPoint& _point
		,	const ISurfaceItem::Id& _surfaceItemId ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const TerrainMapData& getTerrainMapData( const QPoint& _point ) const = 0;

	virtual void setEngagedWithGroungItem( const QPoint& _point, const bool _isEngaged ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getObject( const QPoint& _point ) const = 0;

	virtual boost::shared_ptr< Object > getObject( const Object::UniqueId& _id ) const = 0;

	virtual unsigned int getObjectsCount() const = 0;

	virtual void fetchObjects( ObjectsCollection& _collection ) const = 0;

	virtual void fetchSelectedObjects( ObjectsCollection& _collection ) const = 0;

	virtual Object::UniqueId createObject(
			const QPoint& _location
		,	const QString& _objectName ) = 0;

	virtual void selectObjects( const QRect& _rect ) = 0;

	virtual void selectObject( const Object::UniqueId& _id ) = 0;

	virtual void unselectObjects() = 0;

/*---------------------------------------------------------------------------*/

	virtual bool canObjectBePlaced(
			const QPoint& _location
		,	const LocateComponentStaticData& _data ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
