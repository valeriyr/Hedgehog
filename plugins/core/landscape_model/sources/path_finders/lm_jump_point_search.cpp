
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"

#include "containers/cn_matrix.hpp"


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
						,	const QPoint& _toPoint )
{
	_pointsCollection.clear();

	const int engagedCell = -1;
	const int freeCell = -2;

	Tools::Core::Containers::Matrix< int > matrix;
	matrix.resize( _landscape.getWidth(), _landscape.getHeight() );

	for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( unsigned int j = 0; j < _landscape.getHeight(); ++j )
		{
			int cellValue = engagedCell;

			if ( _landscape.canObjectBePlaced( QPoint( i, j ), _forObject.getStaticData() ) )
			{
				cellValue = freeCell;
			}

			matrix.setElement( i, j, cellValue );
		}
	}

	QPoint startPoint( _forObject.getLocation() );
	QPoint finishPoint = _toPoint;

	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};

	bool stop = false;

	int d = 0;
	matrix.setElement( startPoint.x(), startPoint.y(), d );

	do
	{
		stop = true;
		for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < _landscape.getHeight(); ++j )
			{
				if ( matrix.getConstElement( i, j ) == d )
				{
					for ( int k = 0; k < 4; ++k )
					{
						int rx = i + dx[ k ];
						int ry = j + dy[ k ];

						if ( rx < 0 )
							continue;

						if ( (unsigned int)rx >= _landscape.getWidth() )
							continue;

						if ( ry < 0 )
							continue;

						if ( (unsigned int)ry >= _landscape.getHeight() )
							continue;

						if ( matrix.getConstElement( rx, ry ) == freeCell )
						{
							stop = false;
							matrix.setElement( rx, ry, d + 1);
						}
					}
				}
			}
		}
		++d;
	} while ( !stop && matrix.getConstElement( finishPoint.x(), finishPoint.y() ) == freeCell );

	if ( matrix.getConstElement( finishPoint.x(), finishPoint.y() ) == freeCell )
		return;

	int len = matrix.getConstElement( finishPoint.x(), finishPoint.y() );
	d = len;

	int x = finishPoint.x();
	int y = finishPoint.y();

	while ( d > 0 )
	{
		_pointsCollection.push_front( QPoint( x, y ) );
		--d;

		for ( int k = 0; k < 4; ++k )
		{
			int rx = x + dx[ k ];
			int ry = y + dy[ k ];

			if ( rx < 0 )
				continue;

			if ( (unsigned int)rx >= _landscape.getWidth() )
				continue;

			if ( ry < 0 )
				continue;

			if ( (unsigned int)ry >= _landscape.getHeight() )
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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
