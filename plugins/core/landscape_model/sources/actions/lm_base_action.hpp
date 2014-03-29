
#ifndef __LM_BASE_ACTION_HPP__
#define __LM_BASE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iaction.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscapeModel;

class Object;

/*---------------------------------------------------------------------------*/

class BaseAction
	:	public Tools::Core::BaseWrapper< IAction >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	Object& _object );

	virtual ~BaseAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool prepareToProcessing();

	/*virtual*/ bool cancelProcessing();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isInProcessing() const;

/*---------------------------------------------------------------------------*/

	virtual bool prepareToProcessingInternal();

	virtual bool cancelProcessingInternal();

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	ILandscapeModel& m_landscapeModel;

	Object& m_object;

	bool m_isInProcessing;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BASE_ACTION_HPP__
