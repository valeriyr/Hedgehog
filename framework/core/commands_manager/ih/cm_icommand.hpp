
#ifndef __CM_ICOMMAND_HPP__
#define __CM_ICOMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

struct ICommand
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void execute() = 0;

	virtual bool isEnabled() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_ICOMMAND_HPP__
