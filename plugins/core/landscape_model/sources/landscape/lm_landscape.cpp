
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "landscape_model/ih/lm_iobject_type.hpp"
#include "landscape_model/ih/lm_iobject_types_cache.hpp"

#include "landscape_model/sources/object/lm_object.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape(
		const ISurfaceItemsCache& _surfaceItemsCache
	,	const IObjectTypesCache& _objectTypesCache
	)
	:	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_objectTypesCache( _objectTypesCache )
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


boost::intrusive_ptr< ISurfaceItem >
Landscape::getSurfaceItem( const QPoint& _point ) const
{
	assert( _point.x() >= 0 );
	assert( _point.y() >= 0 );

	return m_surfaceItems.getConstElement( _point.x(), _point.y() );

} // Landscape::getSurfaceItem


/*---------------------------------------------------------------------------*/


const TerrainMapData&
Landscape::getTerrainMapData( const QPoint& _point ) const
{
	assert( _point.x() >= 0 );
	assert( _point.y() >= 0 );

	return m_terrainMap.getConstElement( _point.x(), _point.y() );

} // Landscape::getTerrainMapData


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IObject >
Landscape::getObject( const QPoint& _point ) const
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getRect().contains( _point ) )
			return *begin;
	}

	return boost::intrusive_ptr< IObject >();

} // Landscape::getObject


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IObject >
Landscape::getObject( const IObject::IdType& _id ) const
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getUniqueId() == _id )
			return *begin;
	}

	return boost::intrusive_ptr< IObject >();

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


bool
Landscape::canObjectBePlaced(
		const QPoint& _position
	,	boost::intrusive_ptr< IObjectType > _objectType ) const
{
	for ( int x = _position.x(); x < _position.x() + _objectType->getSize().width(); ++x )
	{
		for ( int y = _position.y(); y < _position.y() + _objectType->getSize().height(); ++y )
		{
			if (	!( _objectType->getPassability() & m_terrainMap.getConstElement( x, y ).m_terrainMapItem )
				||	m_terrainMap.getConstElement( x, y ).m_engagedWithGround )
			{
				return false;
			}
		}
	}

	return true;

} // Landscape::canObjectBePlaced


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


void
Landscape::setSurfaceItem(
		const QPoint& _point
	,	const ISurfaceItem::IdType& _surfaceItemId )
{
	assert( _point.x() >= 0 );
	assert( _point.y() >= 0 );

	boost::intrusive_ptr< ISurfaceItem > surfaceItem = m_surfaceItemsCache.getSurfaceItem( _surfaceItemId );
	assert( surfaceItem );

	m_surfaceItems.setElement( _point.x(), _point.y(), surfaceItem );
	m_terrainMap.getElement( _point.x(), _point.y() ).m_terrainMapItem = surfaceItem->getTerrainMapValue();

} // Landscape::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::setEngagedWithGroungItem( const QPoint& _point, const bool _isEngaged )
{
	m_terrainMap.getElement( _point.x(), _point.y() ).m_engagedWithGround = _isEngaged;

} // Landscape::setEngagedWithGroungItem


/*---------------------------------------------------------------------------*/


IObject::IdType
Landscape::createObject( const QPoint& _position, const QString& _objectName )
{
	boost::intrusive_ptr< IObjectType > objectType = m_objectTypesCache.getObjectType( _objectName );
	assert( objectType );

	if ( canObjectBePlaced( _position, objectType ) )
	{
		boost::intrusive_ptr< IObject > object( new Object( objectType, _position ) );
		m_objects.push_back( object );

		QRect objectRect( object->getRect() );

		for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
		{
			for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
			{
				m_terrainMap.getElement( x, y ).m_engagedWithGround = true;
			}
		}

		return object->getUniqueId();
	}

	return IObject::ms_wrongId;

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
		if ( ( *begin )->getRect().intersects( _rect ) )
		{
			m_selectedObjects.push_back( *begin );
		}
	}

} // Landscape::selectObjects


/*---------------------------------------------------------------------------*/


void
Landscape::selectObject( const IObject::IdType& _id )
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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
