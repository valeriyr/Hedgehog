
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_terrain_map_data.hpp"
#include "landscape_model/h/lm_object.hpp"
#include "landscape_model/h/lm_start_point.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"

#include "iterators/it_iiterator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct IObjectsFilter
	{
		virtual bool check( const Object& _object ) const = 0;
	};

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

	typedef
		boost::shared_ptr< Tools::Core::IIterator< const StartPoint > >
		StartPointsIterator;

/*---------------------------------------------------------------------------*/

	virtual int getWidth() const = 0;

	virtual int getHeight() const = 0;

	virtual void setSize( const int _width, const int _height ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void addStartPoint( const StartPoint& _startPoint ) = 0;

	virtual const StartPoint& getStartPoint( const Tools::Core::Generators::IGenerator::IdType& _startPointId ) = 0;

	virtual StartPointsIterator getStartPointsIterator() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const = 0;

	virtual void setSurfaceItem(
			const QPoint& _point
		,	const Tools::Core::Generators::IGenerator::IdType& _surfaceItemId ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const TerrainMapData& getTerrainMapData( const QPoint& _point ) const = 0;

	virtual void setEngaged( const QPoint& _point, const Emplacement::Enum _emplacement, const bool _isEngaged ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getObject( const QPoint& _point ) const = 0;

	virtual boost::shared_ptr< Object > getObject( const Tools::Core::Generators::IGenerator::IdType& _id ) const = 0;

	virtual int getObjectsCount() const = 0;

	virtual void fetchObjects( ObjectsCollection& _collection ) const = 0;

	virtual void fetchObjects( ObjectsCollection& _collection, const IObjectsFilter& _filter ) const = 0;

	virtual void fetchSelectedObjects( ObjectsCollection& _collection ) const = 0;

	virtual Tools::Core::Generators::IGenerator::IdType createObject(
			const QString& _objectName
		,	const QPoint& _location
		,	const Tools::Core::Generators::IGenerator::IdType& _playerId ) = 0;

	virtual Tools::Core::Generators::IGenerator::IdType createObjectForBuilding(
			const QString& _objectName
		,	const QPoint& _location
		,	const Tools::Core::Generators::IGenerator::IdType& _playerId ) = 0;

	virtual boost::shared_ptr< Object > hideObject( const Tools::Core::Generators::IGenerator::IdType& _id ) = 0;

	virtual void showObject( boost::shared_ptr< Object > _object ) = 0;

	virtual void selectObjects( const IObjectsFilter& _filter ) = 0;

	virtual void unselectObjects() = 0;

/*---------------------------------------------------------------------------*/

	virtual bool canObjectBePlaced(
			const QPoint& _location
		,	const QString& _objectName ) const = 0;

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
