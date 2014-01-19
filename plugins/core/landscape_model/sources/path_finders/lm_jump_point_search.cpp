
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"


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
						,	const ILocateComponent& _forObject
						,	const IPathFinder::PointsCollection& _targets )
{
	_pointsCollection.clear();

	if ( _targets.empty() )
		return;

	Tools::Core::Containers::Matrix< int > matrix;
	matrix.resize( _landscape.getWidth(), _landscape.getHeight() );

	for ( int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			int cellValue = ms_engagedCell;

			if ( _landscape.canObjectBePlaced( QPoint( i, j ), _forObject.getStaticData() ) )
			{
				cellValue = ms_freeCell;
			}

			matrix.setElement( i, j, cellValue );
		}
	}

	QPoint startPoint( _forObject.getLocation() );

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

						if ( rx < 0 )
							continue;

						if ( rx >= _landscape.getWidth() )
							continue;

						if ( ry < 0 )
							continue;

						if ( ry >= _landscape.getHeight() )
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
	} while ( !stop && allPointsFree( matrix, _targets ) );

	if ( allPointsFree( matrix, _targets ) )
		return;

	QPoint finishPoint = getFirstFoundPoint( matrix, _targets );

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

			if ( rx < 0 )
				continue;

			if ( rx >= _landscape.getWidth() )
				continue;

			if ( ry < 0 )
				continue;

			if ( ry >= _landscape.getHeight() )
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


bool
JumpPointSearch::allPointsFree(
		const Tools::Core::Containers::Matrix< int >& matrix
	,	const IPathFinder::PointsCollection& _targets ) const
{
	assert( !_targets.empty() );

	IPathFinder::PointsCollectionConstIterator
			begin = _targets.begin()
		,	end = _targets.end();

	for ( ; begin != end; ++begin )
	{
		if ( matrix.getConstElement( begin->x(), begin->y() ) != ms_freeCell )
			return false;
	}

	return true;

} // JumpPointSearch::allPointsFree


/*---------------------------------------------------------------------------*/


QPoint
JumpPointSearch::getFirstFoundPoint(
		const Tools::Core::Containers::Matrix< int >& matrix
	,	const IPathFinder::PointsCollection& _targets ) const
{
	IPathFinder::PointsCollectionConstIterator
			begin = _targets.begin()
		,	end = _targets.end();

	for ( ; begin != end; ++begin )
	{
		if ( matrix.getConstElement( begin->x(), begin->y() ) != ms_freeCell )
			return *begin;
	}

	assert( !"You should check collection before call this function!" );

	return QPoint();

} // JumpPointSearch::getFirstFoundPoint


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
