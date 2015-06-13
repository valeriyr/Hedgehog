
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/path_finders/lm_astar_search.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


AStarSearch::AStarSearch()
	:	m_openedList()
	,	m_closedList()
{
} // AStarSearch::AStarSearch


/*---------------------------------------------------------------------------*/


AStarSearch::~AStarSearch()
{
} // AStarSearch::~AStarSearch


/*---------------------------------------------------------------------------*/


void
AStarSearch::findPath(
		PointsCollection& _pointsCollection
	,	const ILandscape& _landscape
	,	const GameObject& _object
	,	const IPathFinder::PointsCollection& _targets )
{
	_pointsCollection.clear();

	if ( _targets.empty() )
		return;

	Tools::Core::Object::Ptr locateComponent = _object.getMemberObject( LocateComponent::Name );

	if ( !locateComponent )
		return;

	QPoint startPoint( locateComponent->getMember< QPoint >( LocateComponent::Location ) );

	PointData startPointData;

	startPointData.m_point = startPoint;
	startPointData.m_parentPoint = startPoint;
	startPointData.m_g = 0;
	startPointData.m_h = Geometry::getDistance( startPoint, _targets.front() );
	startPointData.m_f = startPointData.m_h + startPointData.m_g;

	m_openedList.push_back( startPointData );

	while ( !m_openedList.empty() )
		processOpenedList( _landscape, _object, locateComponent, _targets );

	// Path is not found
	if ( m_closedList.empty() || m_closedList.back().m_h != 0 )
		return;

	assert( m_closedList.size() > 1 );

	PointData currentPointData( m_closedList.back() );

	while( currentPointData.m_point != startPoint )
	{
		_pointsCollection.push_front( currentPointData.m_point );
		currentPointData = m_closedList[ findInList( currentPointData.m_parentPoint, m_closedList ) ];
	}

} // AStarSearch::findPath


/*---------------------------------------------------------------------------*/


void
AStarSearch::pathToObject(
		PointsCollection& _path
	,	const ILandscape& _landscape
	,	const GameObject& _forObject
	,	const GameObject& _targetObject
	,	const int _distance )
{
	IPathFinder::PointsCollection targetPoints;

	fillTargetPoints( _targetObject, _landscape, _distance, targetPoints );

	AStarSearch().findPath( _path, _landscape, _forObject, targetPoints );

} // AStarSearch::pathToObject


/*---------------------------------------------------------------------------*/


boost::shared_ptr< GameObject >
AStarSearch::nearestObject(
		const ILandscape& _landscape
	,	const GameObject& _forObject
	,	const ILandscape::ObjectsCollection& _targetObjects
	,	const int _distance )
{
	IPathFinder::PointsCollection targetPoints;

	ILandscape::ObjectsCollectionConstIterator
			begin = _targetObjects.begin()
		,	end = _targetObjects.end();

	for ( ; begin != end; ++begin )
		fillTargetPoints( **begin, _landscape, _distance, targetPoints );

	PointsCollection path;
	AStarSearch().findPath( path, _landscape, _forObject, targetPoints );

	if ( path.empty() )
		return boost::shared_ptr< GameObject >();

	begin = _targetObjects.begin();

	for ( ; begin != end; ++begin )
	{
		if ( Geometry::checkDistance(
					path.back()
				,	LocateComponent::getRect( *( *begin )->getMemberObject( LocateComponent::Name ) )
				,	_distance ) )
		{
			return *begin;
		}
	}

	return boost::shared_ptr< GameObject >();

} // AStarSearch::nearestObject


/*---------------------------------------------------------------------------*/


void
AStarSearch::pathToPoint(
		PointsCollection& _path
	,	const ILandscape& _landscape
	,	const GameObject& _forObject
	,	const QPoint& _targetPoint )
{
	IPathFinder::PointsCollection targetPoints;
	targetPoints.push_back( _targetPoint );

	AStarSearch().findPath( _path, _landscape, _forObject, targetPoints );

} // AStarSearch::pathToPoint


/*---------------------------------------------------------------------------*/


void
AStarSearch::fillTargetPoints(
		const GameObject& _targetObject
	,	const ILandscape& _landscape
	,	const int _distance
	,	IPathFinder::PointsCollection& _targets )
{
	Tools::Core::Object::Ptr targetLocateComponent = _targetObject.getMemberObject( LocateComponent::Name );

	QRect targetRect = LocateComponent::getRect( *targetLocateComponent );

	int distance = _distance / Geometry::NeighborDistance;

	for ( int x = targetRect.x() - distance; x < targetRect.x() + targetRect.width() + distance; ++x )
	{
		for ( int y = targetRect.y() - distance; y < targetRect.y() + targetRect.height() + distance; ++y )
		{
			QPoint location( x, y );
			if ( _landscape.isLocationInLandscape( location ) && Geometry::checkDistance( location, targetRect, _distance ) )
				_targets.push_back( location );
		}
	}

} // AStarSearch::fillTargetPoints


/*---------------------------------------------------------------------------*/


void
AStarSearch::processOpenedList(
		const ILandscape& _landscape
	,	const GameObject& _forObject
	,	Tools::Core::Object::Ptr _locateComponent
	,	const IPathFinder::PointsCollection& _targets )
{
	if ( m_openedList.empty() )
		return;

	int dx[ 8 ] = {  0, 0, -1, 1,  1, 1, -1, -1 };
	int dy[ 8 ] = { -1, 1,  0, 0, -1, 1,  1, -1 };

	int currentPointIndex = findWithMinDistanceInList( m_openedList );
	AStarSearch::PointData pointData = m_openedList[ currentPointIndex ];

	if ( pointData.m_h == 0 )
	{
		m_closedList.push_back( pointData );
		m_openedList.clear();
		return;
	}

	for ( int i = 0; i < 8; ++i )
	{
		QPoint neighbor( pointData.m_point.x() + dx[ i ], pointData.m_point.y() + dy[ i ] );

		if (	!_landscape.isLocationInLandscape( neighbor )
			||	!_landscape.canObjectBePlaced( neighbor, _forObject.getMember< QString >( ObjectNameKey ) )
			||	findInList( neighbor, m_closedList ) != -1 )
		{
			continue;
		}

		PointData neighborData;

		neighborData.m_point = neighbor;
		neighborData.m_parentPoint = pointData.m_point;
		neighborData.m_g = pointData.m_g + Geometry::getDistance( pointData.m_point, neighbor );
		neighborData.m_h = Geometry::getDistance( neighbor, _targets.front() );
		neighborData.m_f = neighborData.m_h + neighborData.m_g;

		int foundNeighborDataIndex = findInList( neighbor, m_openedList );

		if ( foundNeighborDataIndex == -1 )
		{
			m_openedList.push_back( neighborData );
		}
		else if ( m_openedList[ foundNeighborDataIndex ].m_g > neighborData.m_g )
		{
			m_openedList[ foundNeighborDataIndex ] = neighborData;
		}
	}

	m_closedList.push_back( pointData );
	m_openedList.erase( m_openedList.begin() + currentPointIndex );

} // AStarSearch::processOpenedList


/*---------------------------------------------------------------------------*/


int
AStarSearch::findInList( const QPoint& _point, AStarSearch::PointsDataList& _inList )
{
	for ( int i = 0; i < static_cast< int >( _inList.size() ); ++i )
	{
		if ( _inList[ i ].m_point == _point )
			return i;
	}

	return -1;

} // AStarSearch::findInList


/*---------------------------------------------------------------------------*/


int
AStarSearch::findWithMinDistanceInList( AStarSearch::PointsDataList& _inList )
{
	if ( _inList.empty() )
		return -1;

	int minDistance = _inList[ 0 ].m_f;
	int result = 0;

	for ( int i = 1; i < static_cast< int >( _inList.size() ); ++i )
	{
		if ( _inList[ i ].m_f < minDistance )
		{
			minDistance = _inList[ i ].m_f;
			result = i;
		}
	} 

	return result;
}


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
