
#ifndef __ST_IENVIRONMENT_HPP__
#define __ST_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void riseEvent( const Framework::Core::EventManager::Event& _event ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __ST_IENVIRONMENT_HPP__
