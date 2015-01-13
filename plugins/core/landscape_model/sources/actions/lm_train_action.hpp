
#ifndef __LM_TRAIN_ACTION_HPP__
#define __LM_TRAIN_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class TrainAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	TrainAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	GameObject& _object
		,	const QString& _trainObjectName );

	virtual ~TrainAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool prepareToProcessingInternal();

	/*virtual*/ bool cancelProcessing();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

	const QString& getTrainObjectName() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QString m_trainObjectName;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TRAIN_ACTION_HPP__
