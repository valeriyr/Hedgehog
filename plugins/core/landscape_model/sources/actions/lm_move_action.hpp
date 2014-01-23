
#ifndef __LM_MOVE_ACTION_HPP__
#define __LM_MOVE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IPathFinder;
struct ILandscape;

/*---------------------------------------------------------------------------*/

class MoveAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MoveAction(
			const IEnvironment& _environment
		,	Object& _object
		,	ILandscape& _landscape
		,	boost::intrusive_ptr< IPathFinder > _pathFinder
		,	const float _distance );

	virtual ~MoveAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ void unprocessAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void updateWithData( const QVariant& _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void fillPossibleTargetPoints(
			IPathFinder::PointsCollection& _points
		,	const IMoveComponent::MovingData& _movingData ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	ILandscape& m_landscape;

	boost::intrusive_ptr< IPathFinder > m_pathFinder;

	bool m_movingFinished;

	const float m_distance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MOVE_ACTION_HPP__
