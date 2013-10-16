
#include "script_engine/sources/ph/se_ph.hpp"

#include "script_engine/sources/scripts_executor/se_scripts_executor.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/


ScriptsExecutor::ScriptsExecutor()
	:	m_luaEngine( lua_open() )
{
} // ScriptsExecutor::ScriptsExecutor


/*---------------------------------------------------------------------------*/


ScriptsExecutor::~ScriptsExecutor()
{
	lua_close( m_luaEngine );

} // ScriptsExecutor::~ScriptsExecutor


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::executeFile( const QString& _fileName )
{
	int result = luaL_loadfile( m_luaEngine, _fileName.toLocal8Bit().data() );

	if ( result != 0 ) 
	{
		// error lua_tostring(g_LuaVM, -1)
		return;
	}

	result = lua_pcall( m_luaEngine, 0, LUA_MULTRET, 0 );

} // ScriptsExecutor::executeFile


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::executeScript( const QString& _script )
{
	int result = luaL_loadstring( m_luaEngine, _script.toLocal8Bit().data() );

	if ( result != 0 ) 
	{
		// error lua_tostring(g_LuaVM, -1)
		return;
	}

	result = lua_pcall( m_luaEngine, 0, LUA_MULTRET, 0 );

} // ScriptsExecutor::executeScript


/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
