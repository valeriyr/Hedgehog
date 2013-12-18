
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

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
						,	const IUnit& _forUnit
						,	const QPoint& _toPoint )
{
	_pointsCollection.clear();

	const int engagedCell = -1;
	const int freeCell = -2;

	Tools::Core::Containers::Matrix< int > matrix;
	matrix.resize( _landscape.getWidth(), _landscape.getHeight() );

	for ( int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			int cellValue = engagedCell;

			if (	( _forUnit.getType()->getPassability() & _landscape.getTerrainMapData( QPoint( i, j ) ).m_terrainMapItem )
				&&	 !_landscape.getTerrainMapData( QPoint( i, j ) ).m_engagedWithGround )
			{
				cellValue = freeCell;
			}

			matrix.setElement( i, j, cellValue );
		}
	}

	QPoint startPoint( _forUnit.getPosition().x(), _forUnit.getPosition().y() );
	QPoint finishPoint = _toPoint;

	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};

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
					for ( int k = 0; k < 4; ++k )
					{
						if ( matrix.getConstElement( i + dx[ k ], j + dy[ k ] ) == freeCell )
						{
							stop = false;
							matrix.setElement( i + dx[k], j + dy[k], d + 1);
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
			if ( matrix.getConstElement( x + dx[ k ], y + dy[ k ] ) == d )
			{
				x = x + dx[k];
				y = y + dy[k];
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
