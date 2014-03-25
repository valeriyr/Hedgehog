
#ifndef __LM_BUILD_ACTION_HPP__
#define __LM_BUILD_ACTION_HPP__

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

struct ILandscapeModel;
struct IPathFinder;
struct IStaticData;

/*---------------------------------------------------------------------------*/

class BuildAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BuildAction(
			const IEnvironment& _environment
		,	Object& _object
		,	IPlayer& _player
		,	ILandscape& _landscape
		,	ILandscapeModel& _landscapeModel
		,	const IStaticData& _staticData
		,	boost::intrusive_ptr< IPathFinder > _pathFinder );

	virtual ~BuildAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IPlayer& m_player;

	ILandscape& m_landscape;

	ILandscapeModel& m_landscapeModel;

	const IStaticData& m_staticData;

	boost::intrusive_ptr< IPathFinder > m_pathFinder;

	boost::intrusive_ptr< IAction > m_moveAction;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BUILD_ACTION_HPP__
