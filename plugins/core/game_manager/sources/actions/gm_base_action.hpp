
#ifndef __GM_BASE_ACTION_HPP__
#define __GM_BASE_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "game_manager/sources/actions/gm_iaction.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class BaseAction
	:	public Tools::Core::BaseWrapper< IAction >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseAction( const IEnvironment& _environment );

	virtual ~BaseAction();

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_BASE_ACTION_HPP__