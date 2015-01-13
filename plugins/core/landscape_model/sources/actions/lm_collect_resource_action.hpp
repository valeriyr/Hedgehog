
#ifndef __LM_COLLECT_RESOURCE_ACTION_HPP__
#define __LM_COLLECT_RESOURCE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/h/lm_constants.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IWorkersHolder;

/*---------------------------------------------------------------------------*/

class CollectResourceAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CollectResourceAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	IWorkersHolder& _workersHolder
		,	GameObject& _object
		,	boost::shared_ptr< GameObject > _resourceSource );

	CollectResourceAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	IWorkersHolder& _workersHolder
		,	boost::shared_ptr< GameObject > _resourceStorage
		,	GameObject& _object );

	virtual ~CollectResourceAction();

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

	bool ensureStorage();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IWorkersHolder& m_workersHolder;

	boost::shared_ptr< GameObject > m_hiddenObject;

	boost::shared_ptr< GameObject > m_targetObject;

	boost::shared_ptr< GameObject > m_resourceSource;

	boost::shared_ptr< GameObject > m_resourceStarage;

	TickType m_collectingTicksCounter;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COLLECT_RESOURCE_ACTION_HPP__
