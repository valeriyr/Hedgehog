
#ifndef __LM_TRAIN_ACTION_HPP__
#define __LM_TRAIN_ACTION_HPP__

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

/*---------------------------------------------------------------------------*/

class TrainAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	TrainAction(
			const IEnvironment& _environment
		,	Object& _object
		,	IPlayer& _player
		,	ILandscape& _landscape
		,	ILandscapeModel& _landscapeModel );

	virtual ~TrainAction();

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

	IPlayer& m_player;

	ILandscape& m_landscape;

	ILandscapeModel& m_landscapeModel;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TRAIN_ACTION_HPP__
