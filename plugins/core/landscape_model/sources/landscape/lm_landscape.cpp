
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "landscape_model/h/lm_object.hpp"
#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/sources/components/lm_builder_component.hpp"
#include "landscape_model/sources/components/lm_health_component.hpp"
#include "landscape_model/sources/components/lm_locate_component.hpp"
#include "landscape_model/sources/components/lm_selection_component.hpp"
#include "landscape_model/sources/components/lm_actions_component.hpp"
#include "landscape_model/sources/components/lm_move_component.hpp"
#include "landscape_model/sources/components/lm_generate_resources_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape(
		const ISurfaceItemsCache& _surfaceItemsCache
	,	const IStaticData& _staticData
	)
	:	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_staticData( _staticData )
	,	m_objects()
	,	m_selectedObjects()
	,	m_surfaceItems()
	,	m_terrainMap()
{
} // Landscape::Landscape


/*---------------------------------------------------------------------------*/


Landscape::~Landscape()
{
} // Landscape::~Landscape


/*---------------------------------------------------------------------------*/


unsigned int
Landscape::getWidth() const
{
	return m_surfaceItems.getWidth();

} // Landscape::getWidth


/*---------------------------------------------------------------------------*/


unsigned int
Landscape::getHeight() const
{
	return m_surfaceItems.getHeight();

} // Landscape::getHeight


/*---------------------------------------------------------------------------*/


void
Landscape::setSize( const unsigned int _width, const unsigned int _height )
{
	m_objects.clear();
	m_selectedObjects.clear();

	m_surfaceItems.resize( _width, _height );
	m_terrainMap.resize( _width, _height );

	for ( unsigned int i = 0; i < _width; ++i )
	{
		for ( unsigned int j = 0; j < _height; ++j )
		{
			m_surfaceItems.setElement( i, j, m_surfaceItemsCache.getDefaultSurfaceItem() );
			m_terrainMap.getElement( i, j ).m_terrainMapItem = m_surfaceItemsCache.getDefaultSurfaceItem()->getTerrainMapValue();
		}
	}

} // Landscape::setSize


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItem >
Landscape::getSurfaceItem( const QPoint& _point ) const
{
	assert( _point.x() >= 0 );
	assert( _point.y() >= 0 );

	return m_surfaceItems.getConstElement( _point.x(), _point.y() );

} // Landscape::getSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::setSurfaceItem(
		const QPoint& _point
	,	const ISurfaceItem::Id& _surfaceItemId )
{
	assert( _point.x() >= 0 );
	assert( _point.y() >= 0 );

	boost::intrusive_ptr< ISurfaceItem > surfaceItem = m_surfaceItemsCache.getSurfaceItem( _surfaceItemId );
	assert( surfaceItem );

	m_surfaceItems.setElement( _point.x(), _point.y(), surfaceItem );
	m_terrainMap.getElement( _point.x(), _point.y() ).m_terrainMapItem = surfaceItem->getTerrainMapValue();

} // Landscape::setSurfaceItem


/*---------------------------------------------------------------------------*/


const TerrainMapData&
Landscape::getTerrainMapData( const QPoint& _point ) const
{
	assert( _point.x() >= 0 );
	assert( _point.y() >= 0 );

	return m_terrainMap.getConstElement( _point.x(), _point.y() );

} // Landscape::getTerrainMapData


/*---------------------------------------------------------------------------*/


void
Landscape::setEngagedWithGroungItem( const QPoint& _point, const bool _isEngaged )
{
	m_terrainMap.getElement( _point.x(), _point.y() ).m_engagedWithGround = _isEngaged;

} // Landscape::setEngagedWithGroungItem


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
Landscape::getObject( const QPoint& _point ) const
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getComponent< ILocateComponent >( ComponentId::Locate )->getRect().contains( _point ) )
			return *begin;
	}

	return boost::shared_ptr< Object >();

} // Landscape::getObject


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
Landscape::getObject( const Object::UniqueId& _id ) const
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getUniqueId() == _id )
			return *begin;
	}

	return boost::shared_ptr< Object >();

} // Landscape::getObject


/*---------------------------------------------------------------------------*/


unsigned int
Landscape::getObjectsCount() const
{
	return static_cast< unsigned int >( m_objects.size() );

} // Landscape::getObjectsCount


/*---------------------------------------------------------------------------*/


void
Landscape::fetchObjects( ILandscape::ObjectsCollection& _collection ) const
{
	_collection = m_objects;

} // Landscape::fetchObjects


/*---------------------------------------------------------------------------*/


void
Landscape::fetchSelectedObjects( ILandscape::ObjectsCollection& _collection ) const
{
	_collection = m_selectedObjects;

} // Landscape::fetchSelectedObjects


/*---------------------------------------------------------------------------*/


Object::UniqueId
Landscape::createObject( const QPoint& _location, const QString& _objectName )
{
	IStaticData::ObjectStaticData staticData = m_staticData.getObjectStaticData( _objectName );

	if ( canObjectBePlaced( _location, *staticData.m_locateData ) )
	{
		boost::shared_ptr< Object > object( new Object( _objectName ) );

		if ( staticData.m_healthData )
			object->addComponent(
					ComponentId::Health
				,	boost::intrusive_ptr< IComponent >( new HealthComponent( *object, *staticData.m_healthData ) ) );

		if ( staticData.m_locateData )
			object->addComponent(
					ComponentId::Locate
				,	boost::intrusive_ptr< IComponent >( new LocateComponent( *object, *staticData.m_locateData, _location ) ) );

		if ( staticData.m_selectionData )
			object->addComponent(
					ComponentId::Selection
				,	boost::intrusive_ptr< IComponent >( new SelectionComponent( *object, *staticData.m_selectionData ) ) );

		if ( staticData.m_builderData )
			object->addComponent(
					ComponentId::Builder
				,	boost::intrusive_ptr< IComponent >( new BuilderComponent( *object, *staticData.m_builderData ) ) );

		if ( staticData.m_actionsData )
			object->addComponent(
					ComponentId::Actions
				,	boost::intrusive_ptr< IComponent >( new ActionsComponent( *object, *staticData.m_actionsData ) ) );

		if ( staticData.m_moveData )
			object->addComponent(
					ComponentId::Move
				,	boost::intrusive_ptr< IComponent >( new MoveComponent( *object, *staticData.m_moveData ) ) );

		if ( staticData.m_generateResourcesData )
			object->addComponent(
					ComponentId::ResourcesGenerating
				,	boost::intrusive_ptr< IComponent >( new GenerateResourcesComponent( *object, *staticData.m_generateResourcesData ) ) );

		m_objects.push_back( object );

		QRect objectRect( object->getComponent< ILocateComponent >( ComponentId::Locate )->getRect() );

		for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
		{
			for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
			{
				m_terrainMap.getElement( x, y ).m_engagedWithGround = true;
			}
		}

		return object->getUniqueId();
	}

	return Object::ms_wrongId;

} // Landscape::createObject


/*---------------------------------------------------------------------------*/


void
Landscape::selectObjects( const QRect& _rect )
{
	unselectObjects();

	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getComponent< ILocateComponent >( ComponentId::Locate )->getRect().intersects( _rect ) )
		{
			m_selectedObjects.push_back( *begin );
		}
	}

} // Landscape::selectObjects


/*---------------------------------------------------------------------------*/


void
Landscape::selectObject( const Object::UniqueId& _id )
{
	unselectObjects();

	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getUniqueId() == _id )
		{
			m_selectedObjects.push_back( *begin );
			break;
		}
	}

} // Landscape::selectObject


/*---------------------------------------------------------------------------*/


void
Landscape::unselectObjects()
{
	m_selectedObjects.clear();

} // Landscape::unselectObjects


/*---------------------------------------------------------------------------*/


bool
Landscape::canObjectBePlaced(
		const QPoint& _location
	,	const LocateComponentStaticData& _data ) const
{
	for ( int x = _location.x(); x < _location.x() + _data.m_size.width(); ++x )
	{
		for ( int y = _location.y(); y < _location.y() + _data.m_size.height(); ++y )
		{
			if (	!( _data.m_passability & m_terrainMap.getConstElement( x, y ).m_terrainMapItem )
				||	m_terrainMap.getConstElement( x, y ).m_engagedWithGround )
			{
				return false;
			}
		}
	}

	return true;

} // Landscape::canObjectBePlaced


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
