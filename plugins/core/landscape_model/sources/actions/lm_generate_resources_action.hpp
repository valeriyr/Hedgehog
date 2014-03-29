
#ifndef __LM_GENERATE_RESOURCES_ACTION_HPP__
#define __LM_GENERATE_RESOURCES_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

#include "landscape_model/h/lm_object.hpp"

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
		,	Object& _object );

	virtual ~GenerateResourcesAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

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
