
#ifndef __SE_SCRIPTS_EXECUTOR_HPP__
#define __SE_SCRIPTS_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "script_engine/ih/se_iscripts_executor.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class ScriptsExecutor
	:	public Tools::Core::BaseWrapper< IScriptsExecutor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ScriptsExecutor( lua_State* _luaEngine, const IEnvironment& _environment );

	virtual ~ScriptsExecutor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void executeFile( const QString& _fileName );

	/*virtual*/ void executeScript( const QString& _script );

/*---------------------------------------------------------------------------*/

	/*virtual*/ FunctionCaller getFunctionCaller();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void printErrorMessage();

/*---------------------------------------------------------------------------*/

	lua_State* m_luaEngine;

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_SCRIPTS_EXECUTOR_HPP__
