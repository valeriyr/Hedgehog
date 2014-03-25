
#ifndef __LM_ATTACK_ACTION_HPP__
#define __LM_ATTACK_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IPlayer;
struct ILandscape;
struct IPathFinder;

/*---------------------------------------------------------------------------*/

class AttackAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AttackAction(
			const IEnvironment& _environment
		,	Object& _object
		,	IPlayer& _player
		,	ILandscape& _landscape
		,	boost::intrusive_ptr< IPathFinder > _pathFinder );

	virtual ~AttackAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void updateWithData( const QVariant& _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IPlayer& m_player;

	ILandscape& m_landscape;

	boost::intrusive_ptr< IPathFinder > m_pathFinder;

	boost::intrusive_ptr< IAction > m_moveAction;

	bool m_attakingFinished;

	int m_attackPhaseCounter;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ATTACK_ACTION_HPP__
