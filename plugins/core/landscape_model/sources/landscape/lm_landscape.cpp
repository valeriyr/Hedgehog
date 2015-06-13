
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "landscape_model/h/lm_game_object.hpp"
#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/sources/landscape/lm_iobjects_creator.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "iterators/it_simple_iterator.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape( const IEnvironment& _environment, IObjectCreator& _objectCreator )
	:	m_environment( _environment )
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
			m_surfaceItems.setElement( i, j, m_environment.getSurfaceItemsCache()->getDefaultSurfaceItem() );
			m_terrainMap.getElement( i, j ).m_terrainMapItem = m_environment.getSurfaceItemsCache()->getDefaultSurfaceItem()->getTerrainMapValue();
		}
	}

} // Landscape::setSize


/*---------------------------------------------------------------------------*/


void
Landscape::addStartPoint( const StartPoint::Type& _startPoint )
{
	Tools::Core::Generators::IGenerator::IdType id = _startPoint.getMember< Tools::Core::Generators::IGenerator::IdType >( StartPoint::Id );

	StartsPointsCollectionIterator iterator = m_startPoints.find( id );
	assert( iterator == m_startPoints.end() );

	m_startPoints.insert( std::make_pair( id, _startPoint ) );

} // Landscape::addStartPoint


/*---------------------------------------------------------------------------*/


const StartPoint::Type&
Landscape::getStartPoint( const Tools::Core::Generators::IGenerator::IdType& _startPointId )
{
	StartsPointsCollectionConstIterator iterator = m_startPoints.find( _startPointId );
	assert( iterator != m_startPoints.end() );

	return iterator->second;

} // Landscape::getStartPoint


/*---------------------------------------------------------------------------*/


ILandscape::StartPointsIterator
Landscape::getStartPointsIterator() const
{
	return
		ILandscape::StartPointsIterator(
			new Tools::Core::SimpleIterator< StartsPointsCollection, Tools::Core::SecondExtractor >( m_startPoints ) );

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
	,	const Tools::Core::Generators::IGenerator::IdType& _surfaceItemId )
{
	assert( _point.x() >= 0 );
	assert( _point.y() >= 0 );

	boost::intrusive_ptr< ISurfaceItem > surfaceItem = m_environment.getSurfaceItemsCache()->getSurfaceItem( _surfaceItemId );
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


boost::shared_ptr< GameObject >
Landscape::getObject( const QPoint& _point ) const
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( LocateComponent::getRect( *( *begin )->getMemberObject( LocateComponent::Name ) ).contains( _point ) )
			return *begin;
	}

	return boost::shared_ptr< GameObject >();

} // Landscape::getObject


/*---------------------------------------------------------------------------*/


boost::shared_ptr< GameObject >
Landscape::getObject( const Tools::Core::Generators::IGenerator::IdType& _id ) const
{
	if ( _id == Tools::Core::Generators::IGenerator::ms_wrongId )
		return boost::shared_ptr< GameObject >();

	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) == _id )
			return *begin;
	}

	return boost::shared_ptr< GameObject >();

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
Landscape::fetchObjects( ObjectsCollection& _collection, const IObjectsFilter& _filter ) const
{
	_collection.clear();

	ILandscape::ObjectsCollectionConstIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( _filter.check( **begin ) )
			_collection.push_back( *begin );
	}

} // Landscape::fetchObjects


/*---------------------------------------------------------------------------*/


void
Landscape::fetchSelectedObjects( ILandscape::ObjectsCollection& _collection ) const
{
	_collection = m_selectedObjects;

} // Landscape::fetchSelectedObjects


/*---------------------------------------------------------------------------*/


Tools::Core::Generators::IGenerator::IdType
Landscape::createObject( const QString& _objectName, const QPoint& _location, const Tools::Core::Generators::IGenerator::IdType& _playerId )
{
	IStaticData::ObjectStaticData staticData = m_environment.getStaticData()->getObjectStaticData( _objectName );

	if ( canObjectBePlaced( _location, _objectName ) )
	{
		boost::shared_ptr< GameObject > object = m_objectCreator.create( _objectName, _location, _playerId );

		m_objects.push_back( object );

		QRect objectRect( LocateComponent::getRect( *object->getMemberObject( LocateComponent::Name ) ) );

		for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
		{
			for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
			{
				m_terrainMap.getElement( x, y ).markAsEngaged( staticData.m_locateData->getMember< Emplacement::Enum >( LocateComponent::StaticData::Emplacement ), true );
			}
		}

		return object->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey );
	}

	return Tools::Core::Generators::IGenerator::ms_wrongId;

} // Landscape::createObject


/*---------------------------------------------------------------------------*/


Tools::Core::Generators::IGenerator::IdType
Landscape::createObjectForBuilding( const QString& _objectName, const QPoint& _location, const Tools::Core::Generators::IGenerator::IdType& _playerId )
{
	boost::shared_ptr< GameObject > object = getObject( createObject( _objectName, _location, _playerId ) );

	if ( object )
	{
		object->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::UnderConstruction;

		//object->getMemberObject( HealthComponent::Name )
		//	->callVoidMethod< const qint32 >( HealthComponent::SetHealth, 1 );
		HealthComponent::setHealth( *object->getMemberObject( HealthComponent::Name ), 1 );

		return object->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey );
	}

	return Tools::Core::Generators::IGenerator::ms_wrongId;

} // Landscape::createObjectForBuilding


/*---------------------------------------------------------------------------*/


boost::shared_ptr< GameObject >
Landscape::hideObject( const Tools::Core::Generators::IGenerator::IdType& _id )
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		if ( ( *begin )->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) == _id )
		{
			boost::shared_ptr< GameObject > object = *begin;

			Tools::Core::Object::Ptr locateComponent = object->getMemberObject( LocateComponent::Name );
			locateComponent->getMember< bool >( LocateComponent::IsHidden ) = true;

			QRect objectRect( LocateComponent::getRect( *locateComponent ) );

			for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
			{
				for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
				{
					m_terrainMap.getElement( x, y ).markAsEngaged( locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) ), false );
				}
			}

			m_objects.erase( std::remove( m_objects.begin(), m_objects.end(), object ), m_objects.end() );

			return object;
		}
	}

	return boost::shared_ptr< GameObject >();

} // Landscape::hideObject


/*---------------------------------------------------------------------------*/


void
Landscape::showObject( boost::shared_ptr< GameObject > _object )
{
	assert( !getObject( _object->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );
	m_objects.push_back( _object );

	Tools::Core::Object::Ptr locateComponent = _object->getMemberObject( LocateComponent::Name );
	locateComponent->getMember< bool >( LocateComponent::IsHidden ) = false;

	QRect objectRect( LocateComponent::getRect( *locateComponent ) );

	for ( int x = objectRect.x(); x < objectRect.x() + objectRect.width(); ++x )
	{
		for ( int y = objectRect.y(); y < objectRect.y() + objectRect.height(); ++y )
		{
			m_terrainMap.getElement( x, y ).markAsEngaged( locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) ), true );
		}
	}

} // Landscape::showObject


/*---------------------------------------------------------------------------*/


void
Landscape::selectObjects( const IObjectsFilter& _filter )
{
	unselectObjects();

	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		Tools::Core::Object::Ptr selectionComponent = ( *begin )->getMemberObject( SelectionComponent::Name );

		if (	selectionComponent
			&&	( *begin )->getMember< ObjectState::Enum >( ObjectStateKey ) != ObjectState::Dying
			&&	_filter.check( **begin ) )
		{
			selectionComponent->getMember< bool >( SelectionComponent::IsSelected ) = true;
			m_selectedObjects.push_back( *begin );
		}
	}

} // Landscape::selectObjects


/*---------------------------------------------------------------------------*/


void
Landscape::unselectObjects()
{
	ILandscape::ObjectsCollectionIterator
			begin = m_objects.begin()
		,	end = m_objects.end();

	for ( ; begin != end; ++begin )
	{
		Tools::Core::Object::Ptr selectionComponent = ( *begin )->getMemberObject( SelectionComponent::Name );
		assert( selectionComponent );

		selectionComponent->getMember< bool >( SelectionComponent::IsSelected ) = false;
	}

	m_selectedObjects.clear();

} // Landscape::unselectObjects


/*---------------------------------------------------------------------------*/


bool
Landscape::canObjectBePlaced( const QPoint& _location, const QString& _objectName ) const
{
	Tools::Core::Object::Ptr locateData = m_environment.getStaticData()->getObjectStaticData( _objectName ).m_locateData;

	if ( !locateData )
		return false;

	for ( int x = _location.x(); x < _location.x() + locateData->getMember< QSize >( LocateComponent::StaticData::Size ).width(); ++x )
	{
		for ( int y = _location.y(); y < _location.y() + locateData->getMember< QSize >( LocateComponent::StaticData::Size ).height(); ++y )
		{
			if (	x < 0 || x >= getWidth()
				||	y < 0 || y >= getHeight() )
			{
				return false;
			}

			if (	!( locateData->getMember< TerrainMapItem::MaskType >( LocateComponent::StaticData::Passability ) & m_terrainMap.getConstElement( x, y ).m_terrainMapItem )
				||	m_terrainMap.getConstElement( x, y ).canBePlaced( locateData->getMember< Emplacement::Enum >( LocateComponent::StaticData::Emplacement ) ) )
			{
				return false;
			}
		}
	}

	return true;

} // Landscape::canObjectBePlaced


/*---------------------------------------------------------------------------*/


QPoint
Landscape::getNearestLocation( const GameObject& _nearestFrom, const QString& _forObject ) const
{
	Tools::Core::Object::Ptr locateComponent = _nearestFrom.getMemberObject( LocateComponent::Name );

	const QSize& size = locateComponent->getMember< QSize >( StaticDataTools::generateName( LocateComponent::StaticData::Size ) );
	const QPoint& position = locateComponent->getMember< QPoint >( LocateComponent::Location );

	int count = 0;
	int offset = 0;

	while ( count < 5 )
	{
		for ( int y = position.y() - offset; y <= position.y() + size.height() + offset; ++y )
		{
			QPoint result( position.x() + size.width() + offset, y );

			if ( canObjectBePlaced( result, _forObject ) )
				return result;
		}

		for ( int x = position.x() + size.width() - 1 + offset; x >= position.x() - 1 - offset; --x )
		{
			QPoint result( x, position.y() + size.height() + offset );

			if ( canObjectBePlaced( result, _forObject ) )
				return result;
		}

		for ( int y = position.y() + size.height() - 1 + offset; y >= position.y() - 1 - offset; --y )
		{
			QPoint result( position.x() - 1 - offset, y );

			if ( canObjectBePlaced( result, _forObject ) )
				return result;
		}

		for ( int x = position.x() - 1 - offset; x <= position.x() + size.width() + offset; ++x )
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
