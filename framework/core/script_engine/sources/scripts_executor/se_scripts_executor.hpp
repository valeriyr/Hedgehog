
#ifndef __SE_SCRIPTS_EXECUTOR_HPP__
#define __SE_SCRIPTS_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "script_engine/ih/se_iscripts_executor.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

class ScriptsExecutor
	:	public Tools::Core::BaseWrapper< IScriptsExecutor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ScriptsExecutor();

	virtual ~ScriptsExecutor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void executeFile( const QString& _fileName );

	/*virtual*/ void executeScript( const QString& _script );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_SCRIPTS_EXECUTOR_HPP__
