
#ifndef __SE_ISCRIPTS_EXECUTOR_HPP__
#define __SE_ISCRIPTS_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "script_engine/h/se_function_caller.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

	const quint32 IID_SCRIPTS_EXECUTOR = 0;

/*---------------------------------------------------------------------------*/

struct IScriptsExecutor
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void executeFile( const QString& _fileName ) = 0;

	virtual void executeScript( const QString& _script ) = 0;

/*---------------------------------------------------------------------------*/

	virtual FunctionCaller getFunctionCaller() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_ISCRIPTS_EXECUTOR_HPP__
