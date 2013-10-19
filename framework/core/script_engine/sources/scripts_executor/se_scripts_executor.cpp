
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


boost::intrusive_ptr< Tools::Core::IMessenger > ScriptsExecutor::ms_externalMessenger;

void print( boost::intrusive_ptr< Tools::Core::IMessenger >& _messenger, const char* _message )
{
	_messenger->printMessage( _message );
}


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


DataExporter
ScriptsExecutor::getDataExporter()
{
	return DataExporter( m_luaEngine );

} // ScriptsExecutor::getDataExporter


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::setExternalMessenger( boost::intrusive_ptr< Tools::Core::IMessenger > _externalMessenger )
{
	ms_externalMessenger = _externalMessenger;

} // ScriptsExecutor::setExternalMessenger


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Tools::Core::IMessenger >
ScriptsExecutor::getExternalMessenger()
{
	return ms_externalMessenger;

} // ScriptsExecutor::getExternalMessenger


/*---------------------------------------------------------------------------*/


void
ScriptsExecutor::exportScriptAPI()
{
	DataExporter exporter = getDataExporter();

	exporter
		.exportClass< Tools::Core::IMessenger >( "IMessenger" )
			.withMethod( "printMessage", &print );

	exporter.exportFunction( "systemMessenger", &ScriptsExecutor::getExternalMessenger );

} // ScriptsExecutor::exportScriptAPI


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
