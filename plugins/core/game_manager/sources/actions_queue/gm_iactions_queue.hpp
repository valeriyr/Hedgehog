
#ifndef __GM_IACTIONS_QUEUE_HPP__
#define __GM_IACTIONS_QUEUE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

struct IAction;

/*---------------------------------------------------------------------------*/

struct IActionsQueue
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual bool hasActions() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushBackAction( boost::intrusive_ptr< IAction > _action ) = 0;

	virtual boost::intrusive_ptr< IAction > popFrontAction() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_IACTIONS_QUEUE_HPP__
