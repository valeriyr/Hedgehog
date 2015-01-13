
#ifndef __LM_REPAIR_RESOURCE_ACTION_HPP__
#define __LM_REPAIR_RESOURCE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class RepairAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	RepairAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	GameObject& _object
		,	boost::shared_ptr< GameObject > _target );

	virtual ~RepairAction();

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

	boost::shared_ptr< GameObject > m_target;

	int m_healthRepaired;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_REPAIR_RESOURCE_ACTION_HPP__
