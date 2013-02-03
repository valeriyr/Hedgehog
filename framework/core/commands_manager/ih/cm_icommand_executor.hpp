
#ifndef __CM_ICOMMAND_EXECUTOR_HPP__
#define __CM_ICOMMAND_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_COMMAND_EXECUTOR = 1;

/*---------------------------------------------------------------------------*/

struct ICommandExecutor
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void executeCommand( const QString& _command ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_ICOMMAND_EXECUTOR_HPP__
