
#ifndef __LM_JUMP_POINT_SEARCH_HPP__
#define __LM_JUMP_POINT_SEARCH_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/path_finders/lm_ipath_finder.hpp"

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
							 ,	const IUnit& _forUnit
							 ,	const QPoint& _toPoint );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_JUMP_POINT_SEARCH_HPP__
