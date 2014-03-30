
#ifndef __LM_MOVE_ACTION_HPP__
#define __LM_MOVE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/h/lm_object.hpp"

#include "landscape_model/ih/components/lm_imove_component.hpp"

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
		,	Object& _object
		,	const QPoint& _movingTo );

	MoveAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	Object& _object
		,	boost::shared_ptr< Object > _movingTo
		,	const float _distance );

	virtual ~MoveAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool prepareToProcessingInternal();

	/*virtual*/ bool cancelProcessingInternal();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void fillPossibleTargetPoints(
			IPathFinder::PointsCollection& _points
		,	const IMoveComponent::MovingData& _movingData
		,	const ILandscape& _landscape ) const;

	void moveToLocation( const QPoint& _location );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IPathFinder > m_pathFinder;

	bool m_movingFinished;

	QPoint m_movingToPoint;

	boost::shared_ptr< Object > m_movingToObject;
	QPoint m_lastTargetObjectLocation;

	float m_distance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MOVE_ACTION_HPP__
