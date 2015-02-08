
#ifndef __LM_MOVE_ACTION_HPP__
#define __LM_MOVE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/sources/path_finders/lm_ipath_finder.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class MoveAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MoveAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	GameObject& _object
		,	const QPoint& _movingTo );

	MoveAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	GameObject& _object
		,	const QPoint& _movingTo
		,	IPathFinder::PointsCollection& _path );

	MoveAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	GameObject& _object
		,	boost::shared_ptr< GameObject > _movingTo
		,	const int _distance );

	MoveAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	GameObject& _object
		,	boost::shared_ptr< GameObject > _movingTo
		,	IPathFinder::PointsCollection& _path
		,	const int _distance );

	virtual ~MoveAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool prepareToProcessingInternal();

	/*virtual*/ bool cancelProcessingInternal();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void moveToLocation( const QPoint& _location );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QPoint m_movingToPoint;

	boost::shared_ptr< GameObject > m_movingToObject;
	QPoint m_lastTargetObjectLocation;
	IPathFinder::PointsCollection m_preprocessedPath;

	int m_distance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MOVE_ACTION_HPP__
