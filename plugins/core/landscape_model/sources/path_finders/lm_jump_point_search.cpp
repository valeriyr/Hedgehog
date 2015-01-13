
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


JumpPointSearch::JumpPointSearch()
{
} // JumpPointSearch::JumpPointSearch


/*---------------------------------------------------------------------------*/


JumpPointSearch::~JumpPointSearch()
{
} // JumpPointSearch::~JumpPointSearch


/*---------------------------------------------------------------------------*/


void
JumpPointSearch::findPath(	PointsCollection& _pointsCollection
						,	const ILandscape& _landscape
						,	const GameObject& _object
						,	const IPathFinder::PointsCollection& _targets )
{
	_pointsCollection.clear();

	if ( _targets.empty() )
		return;

	boost::intrusive_ptr< ILocateComponent > locateComponent
		= _object.getComponent< ILocateComponent >( ComponentId::Locate );

	if ( !locateComponent )
		return;

	Tools::Core::Containers::Matrix< int > matrix;
	matrix.resize( _landscape.getWidth(), _landscape.getHeight() );

	for ( int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			int cellValue = ms_engagedCell;

			if ( _landscape.canObjectBePlaced( QPoint( i, j ), _object.getMember< QString >( ObjectNameKey ) ) )
			{
				cellValue = ms_freeCell;
			}

			matrix.setElement( i, j, cellValue );
		}
	}

	QPoint startPoint( locateComponent->getLocation() );

	int dx[ 8 ] = {  0, 0, -1, 1,  1, 1, -1, -1 };
	int dy[ 8 ] = { -1, 1,  0, 0, -1, 1,  1, -1 };

	bool stop = false;

	int d = 0;
	matrix.setElement( startPoint.x(), startPoint.y(), d );

	do
	{
		stop = true;
		for ( int i = 0; i < _landscape.getWidth(); ++i )
		{
			for ( int j = 0; j < _landscape.getHeight(); ++j )
			{
				if ( matrix.getConstElement( i, j ) == d )
				{
					for ( int k = 0; k < 8; ++k )
					{
						int rx = i + dx[ k ];
						int ry = j + dy[ k ];

						if ( !_landscape.isLocationInLandscape( QPoint( rx, ry ) ) )
							continue;

						if ( matrix.getConstElement( rx, ry ) == ms_freeCell )
						{
							stop = false;
							matrix.setElement( rx, ry, d + 1);
						}
					}
				}
			}
		}
		++d;
	} while ( !stop && !allPointsFound( matrix, _targets ) );

	if ( !hasFoundPoint( matrix, _targets ) )
		return;

	QPoint finishPoint = getNearestFoundPoint( matrix, _targets, startPoint );

	int len = matrix.getConstElement( finishPoint.x(), finishPoint.y() );
	d = len;

	int x = finishPoint.x();
	int y = finishPoint.y();

	while ( d > 0 )
	{
		_pointsCollection.push_front( QPoint( x, y ) );
		--d;

		for ( int k = 0; k < 8; ++k )
		{
			int rx = x + dx[ k ];
			int ry = y + dy[ k ];

			if ( !_landscape.isLocationInLandscape( QPoint( rx, ry ) ) )
				continue;

			if ( matrix.getConstElement( rx, ry ) == d )
			{
				x = rx;
				y = ry;
				break;
			}
		}
	}

	//_pointsCollection.push_front( startPoint );

} // JumpPointSearch::findPath


/*---------------------------------------------------------------------------*/


void
JumpPointSearch::pathToObject(	PointsCollection& _path
							 ,	const ILandscape& _landscape
							 ,	const GameObject& _forObject
							 ,	const GameObject& _targetObject
							 ,	const int _distance )
{
	IPathFinder::PointsCollection targetPoints;

	fillTargetPoints( _targetObject, _landscape, _distance, targetPoints );

	JumpPointSearch().findPath( _path, _landscape, _forObject, targetPoints );

} // JumpPointSearch::pathToObject


/*---------------------------------------------------------------------------*/


boost::shared_ptr< GameObject >
JumpPointSearch::nearestObject(		const ILandscape& _landscape
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
	JumpPointSearch().findPath( path, _landscape, _forObject, targetPoints );

	if ( path.empty() )
		return boost::shared_ptr< GameObject >();

	begin = _targetObjects.begin();

	for ( ; begin != end; ++begin )
	{
		if ( Geometry::checkDistance(
					path.back()
				,	( *begin )->getComponent< ILocateComponent >( ComponentId::Locate )->getRect()
				,	_distance ) )
		{
			return *begin;
		}
	}

	return boost::shared_ptr< GameObject >();

} // JumpPointSearch::nearestObject


/*---------------------------------------------------------------------------*/


void
JumpPointSearch::pathToPoint(	PointsCollection& _path
							 ,	const ILandscape& _landscape
							 ,	const GameObject& _forObject
							 ,	const QPoint& _targetPoint )
{
	IPathFinder::PointsCollection targetPoints;
	targetPoints.push_back( _targetPoint );

	JumpPointSearch().findPath( _path, _landscape, _forObject, targetPoints );

} // JumpPointSearch::pathToPoint


/*---------------------------------------------------------------------------*/


void
JumpPointSearch::fillTargetPoints(	const GameObject& _targetObject
								,	const ILandscape& _landscape
								,	const int _distance
								,	IPathFinder::PointsCollection& _targets )
{
	boost::intrusive_ptr< ILocateComponent > targetLocateComponent
		= _targetObject.getComponent< ILocateComponent >( ComponentId::Locate );

	QRect targetRect = targetLocateComponent->getRect();

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

} // JumpPointSearch::fillTargetPoints


/*---------------------------------------------------------------------------*/


bool
JumpPointSearch::allPointsFound(
		const Tools::Core::Containers::Matrix< int >& matrix
	,	const IPathFinder::PointsCollection& _targets ) const
{
	IPathFinder::PointsCollectionConstIterator
			begin = _targets.begin()
		,	end = _targets.end();

	for ( ; begin != end; ++begin )
	{
		if ( matrix.getConstElement( begin->x(), begin->y() ) == ms_freeCell )
			return false;
	}

	return true;

} // JumpPointSearch::allPointsFound


/*---------------------------------------------------------------------------*/


bool
JumpPointSearch::hasFoundPoint(
		const Tools::Core::Containers::Matrix< int >& matrix
	,	const IPathFinder::PointsCollection& _targets ) const
{
	IPathFinder::PointsCollectionConstIterator
			begin = _targets.begin()
		,	end = _targets.end();

	for ( ; begin != end; ++begin )
	{
		if ( matrix.getConstElement( begin->x(), begin->y() ) >= 0 )
			return true;
	}

	return false;

} // JumpPointSearch::hasFoundPoint


/*---------------------------------------------------------------------------*/


QPoint
JumpPointSearch::getNearestFoundPoint(
		const Tools::Core::Containers::Matrix< int >& _matrix
	,	const IPathFinder::PointsCollection& _targets
	,	const QPoint& _startPoint ) const
{
	int distance = INT_MAX;
	QPoint result;

	IPathFinder::PointsCollectionConstIterator
			begin = _targets.begin()
		,	end = _targets.end();

	for ( ; begin != end; ++begin )
	{
		if ( _matrix.getConstElement( begin->x(), begin->y() ) >= 0 )
		{
			int temp = Geometry::getDistance( _startPoint, *begin );

			if ( temp < distance )
			{
				distance = temp;
				result = *begin;
			}
		}
	}

	return result;

} // JumpPointSearch::getFoundPoint


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
