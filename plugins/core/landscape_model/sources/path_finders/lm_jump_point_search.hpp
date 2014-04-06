
#ifndef __LM_JUMP_POINT_SEARCH_HPP__
#define __LM_JUMP_POINT_SEARCH_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/path_finders/lm_ipath_finder.hpp"

#include "containers/cn_matrix.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class JumpPointSearch
	:	public Tools::Core::BaseWrapper< IPathFinder >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	JumpPointSearch();

	virtual ~JumpPointSearch();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void findPath(	PointsCollection& _pointsCollection
							 ,	const ILandscape& _landscape
							 ,	const Object& _object
							 ,	const IPathFinder::PointsCollection& _targets );

/*---------------------------------------------------------------------------*/

	static void pathToObject(	PointsCollection& _path
							 ,	const ILandscape& _landscape
							 ,	const Object& _forObject
							 ,	const Object& _targetObject
							 ,	const int _distance );

	static void pathToPoint(	PointsCollection& _path
							 ,	const ILandscape& _landscape
							 ,	const Object& _forObject
							 ,	const QPoint& _targetPoint );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	bool allPointsFound(
			const Tools::Core::Containers::Matrix< int >& matrix
		,	const IPathFinder::PointsCollection& _targets ) const;

	bool hasFoundPoint(
			const Tools::Core::Containers::Matrix< int >& matrix
		,	const IPathFinder::PointsCollection& _targets ) const;

	QPoint getNearestFoundPoint(
			const Tools::Core::Containers::Matrix< int >& _matrix
		,	const IPathFinder::PointsCollection& _targets
		,	const QPoint& _startPoint ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static const int ms_engagedCell = -1;
	static const int ms_freeCell = -2;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_JUMP_POINT_SEARCH_HPP__
