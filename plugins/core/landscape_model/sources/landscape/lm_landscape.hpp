
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

struct IEnvironment;
struct IObjectCreator;

/*---------------------------------------------------------------------------*/

class Landscape
	:	public Tools::Core::BaseWrapper< ILandscape >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Landscape( const IEnvironment& _environment, IObjectCreator& _objectCreator );

	virtual ~Landscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ int getWidth() const;

	/*virtual*/ int getHeight() const;

	/*virtual*/ void setSize( const int _width, const int _height );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addStartPoint( const Tools::Core::Object& _startPoint );

	/*virtual*/ const Tools::Core::Object& getStartPoint( const Tools::Core::Generators::IGenerator::IdType& _startPointId );

	/*virtual*/ ILandscape::StartPointsIterator getStartPointsIterator() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem > getSurfaceItem( const QPoint& _point ) const;

	/*virtual*/ void setSurfaceItem(
			const QPoint& _point
		,	const Tools::Core::Generators::IGenerator::IdType& _surfaceItemId );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const TerrainMapData& getTerrainMapData( const QPoint& _point ) const;

	/*virtual*/ void setEngaged( const QPoint& _point, const Emplacement::Enum _emplacement, const bool _isEngaged );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< Object > getObject( const QPoint& _point ) const;

	/*virtual*/ boost::shared_ptr< Object > getObject( const Tools::Core::Generators::IGenerator::IdType& _id ) const;

	/*virtual*/ int getObjectsCount() const;

	/*virtual*/ void fetchObjects( ILandscape::ObjectsCollection& _collection ) const;

	/*virtual*/ void fetchObjects( ObjectsCollection& _collection, const IObjectsFilter& _filter ) const;

	/*virtual*/ void fetchSelectedObjects( ILandscape::ObjectsCollection& _collection ) const;

	/*virtual*/ Tools::Core::Generators::IGenerator::IdType createObject( const QString& _objectName, const QPoint& _location, const Tools::Core::Generators::IGenerator::IdType& _playerId );

	/*virtual*/ Tools::Core::Generators::IGenerator::IdType createObjectForBuilding( const QString& _objectName, const QPoint& _location, const Tools::Core::Generators::IGenerator::IdType& _playerId );

	/*virtual*/ boost::shared_ptr< Object > hideObject( const Tools::Core::Generators::IGenerator::IdType& _id );

	/*virtual*/ void showObject( boost::shared_ptr< Object > _object );

	/*virtual*/ void selectObjects( const IObjectsFilter& _filter );

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
	
	const IEnvironment& m_environment;
	IObjectCreator& m_objectCreator;

/*---------------------------------------------------------------------------*/

	ILandscape::ObjectsCollection m_objects;
	ILandscape::ObjectsCollection m_selectedObjects;

	Tools::Core::Containers::Matrix< boost::intrusive_ptr< ISurfaceItem > > m_surfaceItems;
	Tools::Core::Containers::Matrix< TerrainMapData > m_terrainMap;

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Tools::Core::Generators::IGenerator::IdType, const Tools::Core::Object >
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
