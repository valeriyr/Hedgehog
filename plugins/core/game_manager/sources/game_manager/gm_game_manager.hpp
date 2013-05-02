
#ifndef __GM_GAME_MANAGER_HPP__
#define __GM_GAME_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "game_manager/ih/gm_igame_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IActionsQueue;

/*---------------------------------------------------------------------------*/

class GameManager
	:	public Tools::Core::BaseWrapper< IGameManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GameManager(
			const IEnvironment& _environment
		,	boost::intrusive_ptr< IActionsQueue > _actionsQueue );

	virtual ~GameManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void run();

	/*virtual*/ void stop();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushMoveAction(
			boost::intrusive_ptr< LandscapeModel::IUnit > _unit
		,	const LandscapeModel::Point& _moveTo );

	/*virtual*/ void pushSelectAction(
			const LandscapeModel::Point& _from
		,	const LandscapeModel::Point& _to );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void runEventsProcessing();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::intrusive_ptr< IActionsQueue > m_actionsQueue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_GAME_MANAGER_HPP__
