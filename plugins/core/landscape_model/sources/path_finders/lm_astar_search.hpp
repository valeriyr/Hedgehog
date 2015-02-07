
#ifndef __LM_ASTAR_SEARCH_HPP__
#define __LM_ASTAR_SEARCH_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/path_finders/lm_ipath_finder.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"

#include "containers/cn_matrix.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILocateComponent;

/*---------------------------------------------------------------------------*/

class AStarSearch
	:	public Tools::Core::BaseWrapper< IPathFinder >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AStarSearch();

	virtual ~AStarSearch();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void findPath(
			PointsCollection& _pointsCollection
		,	const ILandscape& _landscape
		,	const GameObject& _object
		,	const IPathFinder::PointsCollection& _targets );

/*---------------------------------------------------------------------------*/

	static void pathToObject(
			PointsCollection& _path
		,	const ILandscape& _landscape
		,	const GameObject& _forObject
		,	const GameObject& _targetObject
		,	const int _distance );

	static boost::shared_ptr< GameObject >
		nearestObject(
				const ILandscape& _landscape
			,	const GameObject& _forObject
			,	const ILandscape::ObjectsCollection& _targetObjects
			,	const int _distance );

	static void pathToPoint(
			PointsCollection& _path
		,	const ILandscape& _landscape
		,	const GameObject& _forObject
		,	const QPoint& _targetPoint );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static void fillTargetPoints(
			const GameObject& _targetObject
		,	const ILandscape& _landscape
		,	const int _distance
		,	IPathFinder::PointsCollection& _targets );

/*---------------------------------------------------------------------------*/

	void processOpenedList(
			const ILandscape& _landscape
		,	const GameObject& _forObject
		,	Tools::Core::Object::Ptr _locateComponent
		,	const IPathFinder::PointsCollection& _targets );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/


	struct PointData
	{
		QPoint m_point;
		QPoint m_parentPoint;

		// moving cost. 10 - gorizontal and vertical, 14 - diagonal
		int m_g;

		// moving cost from current point to result one
		int m_h;

		// m_g + m_h
		int m_f;
	};

	typedef
		std::vector< PointData >
		PointsDataList;
	typedef
		PointsDataList::iterator
		PointsDataListIterator;

	int findInList( const QPoint& _point, PointsDataList& _inList );

	int findWithMinDistanceInList( PointsDataList& _inList );

/*---------------------------------------------------------------------------*/

	PointsDataList m_openedList;

	PointsDataList m_closedList;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ASTAR_SEARCH_HPP__
