
#ifndef __SE_ISCRIPTS_EXECUTOR_HPP__
#define __SE_ISCRIPTS_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_SCRIPTS_EXECUTOR = 0;

/*---------------------------------------------------------------------------*/

struct IScriptsExecutor
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void executeFile( const QString& _fileName ) = 0;

	virtual void executeScript( const QString& _script ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_ISCRIPTS_EXECUTOR_HPP__
