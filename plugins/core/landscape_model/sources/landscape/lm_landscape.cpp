
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "landscape_model/h/lm_object.hpp"
#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_ihealth_component.hpp"

#include "landscape_model/sources/landscape/lm_iobjects_creator.hpp"

#include "iterators/it_simple_iterator.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape(
		const ISurfaceItemsCache& _surfaceItemsCache
	,	const IStaticData& _staticData
	,	IObjectCreator& _objectCreator
	)
	:	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_staticData( _staticData )
	,	m_objectCreator( _objectCreator )
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


int
Landscape::getWidth() const
{
	return m_surfaceItems.getWidth();

} // Landscape::getWidth


/*---------------------------------------------------------------------------*/


int
Landscape::getHeight() const
{
	return m_surfaceItems.getHeight();

} // Landscape::getHeight


/*---------------------------------------------------------------------------*/


void
Landscape::setSize( const int _width, const int _height )
{
	m_objects.clear();
	m_selectedObjects.clear();

	m_surfaceItems.resize( _width, _height );
	m_terrainMap.resize( _width, _height );

	for ( int i = 0; i < _width; ++i )
	{
		for (  int j = 0; j < _height; ++j )
		{
			m_surfaceItems.setElement( i, j, m_surfaceItemsCache.getDefaultSurfaceItem() );
			m_terrainMap.getElement( i, j ).m_terrainMapItem = m_surfaceItemsCache.getDefaultSurfaceItem()->getTerrainMapValue();
		}
	}

} // Landscape::setSize


/*---------------------------------------------------------------------------*/


void
Landscape::setStartPoint( const IPlayer::Id& _playerId, const QPoint& _point )
{
	StartsPointsCollectionIterator iterator = m_startPoints.find( _playerId );

	if ( iterator == m_startPoints.end() )
		m_startPoints.insert( std::make_pair( _playerId, _point ) );
	else
		iterator->second = _point;

} // Landscape::setStartPoint


/*---------------------------------------------------------------------------*/


QPoint
Landscape::getStartPoint( const IPlayer::Id& _playerId ) const
{
	StartsPointsCollectionConstIterator iterator = m_startPoints.find( _playerId );

	return
			iterator != m_startPoints.end()
		?	iterator->second
		:	QPoint();

} // Landscape::getStartPoint


/*---------------------------------------------------------------------------*/


ILandscape::StartPointsIterator
Landscape::getStartPointsIterator() const
{
	return
		ILandscape::StartPointsIterator(
			new Tools::Core::SimpleIterator< StartsPointsCollection >( m_startPoints ) );

} // Landscape::getStartPointsIterator


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
Landscape::setEngaged( const QPoint& _point, const Emplacement::Enum _emplacement, const bool _isEngaged )
{
	m_terrainMap.getElement( _point.x(), _point.y() ).markAsEngaged( _emplacement, _isEngaged );

} // Landscape::setEngaged


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
Landscape::getObject( const Object::Id& _id ) const
{
	if ( _id == Object::ms_wrongId )
		return boost::shared_ptr< Object >();

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


int
Landscape::getObjectsCount() const
{
	return static_cast< int >( m_objects.size() );

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


Object::Id
Landscape::createObject( const QString& _objectName, const QPoint& _location, const IPlayer::Id& _playerId )
{
	IStaticData::ObjectStaticData staticData = m_staticData.getObjectStaticData( _objectName );

	if ( canObjectBePlaced( _location, _objectName ) )
	{
		boost::shared_ptr< Object > object = m_objectCreator.create( _objectName, _location, _playerId );

		m_objects.push_back( object );

		QRect objectRect( object->getComponent< ILocateComponent >( ComponentId::Locate )->getRect() );

		for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
		{
			for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
			{
				m_terrainMap.getElement( x, y ).markAsEngaged( staticData.m_locateData->m_emplacement, true );
			}
		}

		return object->getUniqueId();
	}

	return Object::ms_wrongId;

} // Landscape::createObject


/*---------------------------------------------------------------------------*/


Object::Id
Landscape::createObjectForBuilding( const QString& _objectName, const QPoint& _location, const IPlayer::Id& _playerId )
{
	boost::shared_ptr< Object > object = getObject( createObject( _objectName, _location, _playerId ) );

	if ( object )
	{
		object->setState( ObjectState::UnderConstruction );
		object->getComponent< IHealthComponent >( ComponentId::Health )->setHealth( 1 );

		return object->getUniqueId();
	}

	return Object::ms_wrongId;

} // Landscape::createObjectForBuilding


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
Landscape::removeObject( const Object::Id& _id )
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getUniqueId() == _id )
		{
			boost::shared_ptr< Object > object = *begin;

			boost::intrusive_ptr< ILocateComponent >
				locateComponent = object->getComponent< ILocateComponent >( ComponentId::Locate );

			QRect objectRect( locateComponent->getRect() );

			for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
			{
				for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
				{
					m_terrainMap.getElement( x, y ).markAsEngaged( locateComponent->getStaticData().m_emplacement, false );
				}
			}

			m_objects.erase( std::remove( m_objects.begin(), m_objects.end(), object ), m_objects.end() );

			return object;
		}
	}

	return boost::shared_ptr< Object >();

} // Landscape::removeObject


/*---------------------------------------------------------------------------*/


void
Landscape::addObject( boost::shared_ptr< Object > _object )
{
	assert( !getObject( _object->getUniqueId() ) );
	m_objects.push_back( _object );

	boost::intrusive_ptr< ILocateComponent >
		locateComponent = _object->getComponent< ILocateComponent >( ComponentId::Locate );

	QRect objectRect( locateComponent->getRect() );

	for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
	{
		for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
		{
			m_terrainMap.getElement( x, y ).markAsEngaged( locateComponent->getStaticData().m_emplacement, true );
		}
	}

} // Landscape::addObject


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
		if (	( *begin )->getState() != ObjectState::Dying
			&&	( *begin )->getComponent< ILocateComponent >( ComponentId::Locate )->getRect().intersects( _rect ) )
		{
			m_selectedObjects.push_back( *begin );
		}
	}

} // Landscape::selectObjects


/*---------------------------------------------------------------------------*/


void
Landscape::selectObject( const Object::Id& _id )
{
	unselectObjects();

	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if (	( *begin )->getState() != ObjectState::Dying
			&&	( *begin )->getUniqueId() == _id )
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
Landscape::canObjectBePlaced( const QPoint& _location, const QString& _objectName ) const
{
	boost::shared_ptr< ILocateComponent::StaticData > locateData
		= m_staticData.getObjectStaticData( _objectName ).m_locateData;

	if ( !locateData )
		return false;

	for ( int x = _location.x(); x < _location.x() + locateData->m_size.width(); ++x )
	{
		for ( int y = _location.y(); y < _location.y() + locateData->m_size.height(); ++y )
		{
			if (	x < 0 || x >= getWidth()
				||	y < 0 || y >= getHeight() )
			{
				return false;
			}

			if (	!( locateData->m_passability & m_terrainMap.getConstElement( x, y ).m_terrainMapItem )
				||	m_terrainMap.getConstElement( x, y ).canBePlaced( locateData->m_emplacement ) )
			{
				return false;
			}
		}
	}

	return true;

} // Landscape::canObjectBePlaced


/*---------------------------------------------------------------------------*/


QPoint
Landscape::getNearestLocation( const Object& _nearestFrom, const QString& _forObject ) const
{
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= _nearestFrom.getComponent< ILocateComponent >( ComponentId::Locate );

	const ILocateComponent::StaticData& staticData = locateComponent->getStaticData();
	const QPoint& position = locateComponent->getLocation();

	int count = 0;
	int offset = 0;

	while ( count < 5 )
	{
		for ( int y = position.y() - offset; y <= position.y() + staticData.m_size.height() + offset; ++y )
		{
			QPoint result( position.x() + staticData.m_size.width() + offset, y );

			if ( canObjectBePlaced( result, _forObject ) )
				return result;
		}

		for ( int x = position.x() + staticData.m_size.width() - 1 + offset; x >= position.x() - 1 - offset; --x )
		{
			QPoint result( x, position.y() + staticData.m_size.height() + offset );

			if ( canObjectBePlaced( result, _forObject ) )
				return result;
		}

		for ( int y = position.y() + staticData.m_size.height() - 1 + offset; y >= position.y() - 1 - offset; --y )
		{
			QPoint result( position.x() - 1 - offset, y );

			if ( canObjectBePlaced( result, _forObject ) )
				return result;
		}

		for ( int x = position.x() - 1 - offset; x <= position.x() + staticData.m_size.width() + offset; ++x )
		{
			QPoint result( x, position.y() - 1 - offset );

			if ( canObjectBePlaced( result, _forObject ) )
				return result;
		}

		++count;
		++offset;
	}

	assert( !"You should handle situation when location point is not found!" );
	return QPoint();

} // Landscape::getNearestLocation


/*---------------------------------------------------------------------------*/


bool
Landscape::isLocationInLandscape( const QPoint& _location ) const
{
	return
			_location.x() >= 0
		&&	_location.x() < getWidth()
		&&	_location.y() >= 0
		&&	_location.y() < getHeight();

} // Landscape::isLocationInLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
