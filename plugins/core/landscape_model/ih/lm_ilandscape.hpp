
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_terrain_map_data.hpp"
#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItem;

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

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const = 0;

	virtual const TerrainMapData& getTerrainMapData( const QPoint& _point ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getObject( const QPoint& _point ) const = 0;

	virtual boost::shared_ptr< Object > getObject( const Object::UniqueId& _id ) const = 0;

	virtual unsigned int getObjectsCount() const = 0;

	virtual void fetchObjects( ObjectsCollection& _collection ) const = 0;

	virtual void fetchSelectedObjects( ObjectsCollection& _collection ) const = 0;

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
