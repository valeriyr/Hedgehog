
#ifndef __LM_IACTIONS_QUEUE_HPP__
#define __LM_IACTIONS_QUEUE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IAction;

/*---------------------------------------------------------------------------*/

struct IActionsQueue
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void pushAction( boost::intrusive_ptr< IAction > _action ) = 0;

	virtual void processAction( const unsigned int _deltaTime ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IACTIONS_QUEUE_HPP__
