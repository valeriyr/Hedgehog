
#ifndef __LM_GENERATE_RESOURCES_ACTION_HPP__
#define __LM_GENERATE_RESOURCES_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class GenerateResourcesAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GenerateResourcesAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	GameObject& _object );

	virtual ~GenerateResourcesAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Actions::Enum getType() const;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_GENERATE_RESOURCES_ACTION_HPP__
