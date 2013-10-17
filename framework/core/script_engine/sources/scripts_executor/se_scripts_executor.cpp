
#include "script_engine/sources/ph/se_ph.hpp"

#include "script_engine/sources/scripts_executor/se_scripts_executor.hpp"

#include "script_engine/sources/environment/se_ienvironment.hpp"
#include "script_engine/sources/resources/se_internal_resources.hpp"

#include "messenger/ms_imessenger.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

ScriptsExecutor::ScriptsExecutor( const IEnvironment& _environment )
	:	m_luaEngine( lua_open() )
	,	m_environment( _environment )
{
	luaopen_base( m_luaEngine );
	luaopen_string(m_luaEngine );

	luabind::open( m_luaEngine );

	exportScriptAPI();

	executeFile( m_environment.getSystemConfigDirectory() + "/" + Resources::SystemScriptFileName );

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


Register
ScriptsExecutor::getRegister()
{
	return Register( m_luaEngine );
}


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::exportScriptAPI()
{
	Register reg = getRegister();

	reg
		.registerClass< Tools::Core::IMessenger >( "Messenger" )
			.withMethod( "printMessage", static_cast< void( Tools::Core::IMessenger::* )( const QString& ) >( &Tools::Core::IMessenger::printMessage ) );

	reg.pushObject( "systemMessenger", m_environment.getSystemMessenger() );

} // ScriptsExecutor::exportScriptAPI


/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
