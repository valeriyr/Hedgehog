
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "landscape_model/ih/lm_iobject_type.hpp"
#include "landscape_model/ih/lm_iobject_types_cache.hpp"

#include "landscape_model/sources/unit/lm_unit.hpp"


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
	,	m_units()
	,	m_selectedUnits()
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


boost::intrusive_ptr< IUnit >
Landscape::getUnit( const QPoint& _point ) const
{
	ILandscape::UnitsCollectionIterator
			begin = m_units.begin()
		,	end = m_units.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getPosition().contains( _point ) )
			return *begin;
	}

	return boost::intrusive_ptr< IUnit >();

} // Landscape::getUnit


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IUnit >
Landscape::getUnit( const IUnit::IdType& _id ) const
{
	ILandscape::UnitsCollectionIterator
			begin = m_units.begin()
		,	end = m_units.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getUniqueId() == _id )
			return *begin;
	}

	return boost::intrusive_ptr< IUnit >();

} // Landscape::getUnit


/*---------------------------------------------------------------------------*/


unsigned int
Landscape::getUnitsCount() const
{
	return static_cast< unsigned int >( m_units.size() );

} // Landscape::getUnitsCount


/*---------------------------------------------------------------------------*/


void
Landscape::fetchUnits( ILandscape::UnitsCollection& _collection ) const
{
	_collection = m_units;

} // Landscape::fetchUnits


/*---------------------------------------------------------------------------*/


void
Landscape::fetchSelectedUnits( ILandscape::UnitsCollection& _collection ) const
{
	_collection = m_selectedUnits;

} // Landscape::fetchSelectedUnits


/*---------------------------------------------------------------------------*/


bool
Landscape::canCreateObject(
		const QPoint& _position
	,	const QString& _objectName ) const
{
	boost::intrusive_ptr< IObjectType > objectType = m_objectTypesCache.getObjectType( _objectName );
	assert( objectType );

	if (	( objectType->getPassability() & m_terrainMap.getConstElement( _position.x(), _position.y() ).m_terrainMapItem )
		&&	!m_terrainMap.getConstElement( _position.x(), _position.y() ).m_engagedWithGround )
	{
		return true;
	}

	return false;

} // Landscape::canCreateObject


/*---------------------------------------------------------------------------*/


void
Landscape::setSize( const unsigned int _width, const unsigned int _height )
{
	m_units.clear();
	m_selectedUnits.clear();

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


IUnit::IdType
Landscape::createObject( const QPoint& _position, const QString& _objectName )
{
	boost::intrusive_ptr< IObjectType > objectType = m_objectTypesCache.getObjectType( _objectName );
	assert( objectType );

	QRect objectRect( _position, objectType->getObjectSize() );

	if ( canCreateObject( _position, _objectName ) )
	{
		boost::intrusive_ptr< IUnit > unit( new Unit( objectType, objectRect ) );

		m_units.push_back( unit );
		m_terrainMap.getElement( objectRect.x(), objectRect.y() ).m_engagedWithGround = true;

		return unit->getUniqueId();
	}

	return IUnit::ms_wrongId;

} // Landscape::createObject


/*---------------------------------------------------------------------------*/


void
Landscape::selectUnits( const QRect& _rect )
{
	unselectUnits();

	ILandscape::UnitsCollectionIterator
			begin = m_units.begin()
		,	end = m_units.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getPosition().intersects( _rect ) )
		{
			m_selectedUnits.push_back( *begin );
		}
	}

} // Landscape::selectUnits


/*---------------------------------------------------------------------------*/


void
Landscape::unselectUnits()
{
	m_selectedUnits.clear();

} // Landscape::unselectUnits


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
