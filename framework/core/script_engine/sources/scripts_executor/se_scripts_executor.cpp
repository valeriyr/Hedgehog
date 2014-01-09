
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


ScriptsExecutor::ScriptsExecutor( lua_State* _luaEngine, const IEnvironment& _environment )
	:	m_luaEngine( _luaEngine )
	,	m_environment( _environment )
{
} // ScriptsExecutor::ScriptsExecutor


/*---------------------------------------------------------------------------*/


ScriptsExecutor::~ScriptsExecutor()
{
} // ScriptsExecutor::~ScriptsExecutor


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::executeFile( const QString& _fileName )
{
	int result = luaL_loadfile( m_luaEngine, _fileName.toLocal8Bit().data() );

	if ( result != 0 ) 
	{
		printErrorMessage();
		return;
	}

	result = lua_pcall( m_luaEngine, 0, LUA_MULTRET, 0 );

	if ( result != 0 ) 
	{
		printErrorMessage();
		return;
	}

} // ScriptsExecutor::executeFile


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::executeScript( const QString& _script )
{
	int result = luaL_loadstring( m_luaEngine, _script.toLocal8Bit().data() );

	if ( result != 0 ) 
	{
		printErrorMessage();
		return;
	}

	result = lua_pcall( m_luaEngine, 0, LUA_MULTRET, 0 );

	if ( result != 0 ) 
	{
		printErrorMessage();
		return;
	}

} // ScriptsExecutor::executeScript


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::printErrorMessage()
{
	m_environment.getSystemMessenger()->printMessage( Tools::Core::IMessenger::MessegeLevel::Error
													, QString( Resources::ScripterMessageFormat ).arg( lua_tostring( m_luaEngine, -1 ) ) );

} // ScriptsExecutor::printErrorMessage


/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
