
#ifndef __LM_BASE_ACTION_HPP__
#define __LM_BASE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_iaction.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
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
		,	Object& _object );

	virtual ~BaseAction();

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Object& m_object;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BASE_ACTION_HPP__
