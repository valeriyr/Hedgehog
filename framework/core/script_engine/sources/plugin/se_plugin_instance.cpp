
#include "script_engine/sources/ph/se_ph.hpp"

#include "script_engine/sources/plugin/se_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "script_engine/h/se_resources.hpp"

#include "script_engine/sources/resources/se_internal_resources.hpp"

#include "script_engine/sources/scripts_executor/se_scripts_executor.hpp"
#include "script_engine/sources/exporter/se_exporter.hpp"
#include "script_engine/sources/environment/se_environment.hpp"

#include "messenger/ms_imessenger.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_SCRIPTS_EXECUTOR, m_scriptsExecutor )
	INTERFACE_DECLARATION( IID_EXPORTER, m_exporter )

END_INTERFACE_MAP()


/*---------------------------------------------------------------------------*/


PluginInstance::PluginInstance()
	:	m_luaEngine( NULL )
{
} // PluginInstance::PluginInstance


/*---------------------------------------------------------------------------*/


PluginInstance::~PluginInstance()
{
} // PluginInstance::~PluginInstance


/*---------------------------------------------------------------------------*/


void
PluginInstance::initialize()
{
	m_luaEngine = lua_open();

	luaopen_base( m_luaEngine );
	luaopen_string( m_luaEngine );
	luaopen_table( m_luaEngine );

	luabind::open( m_luaEngine );

	m_environment.reset( new Environment( *this ) );
	m_scriptsExecutor.reset( new ScriptsExecutor( m_luaEngine, *m_environment ) );
	m_exporter.reset( new Exporter( m_luaEngine, *m_environment ) );

	exportScriptAPI();
	executeConfigurationScripts();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_exporter.reset();
	m_scriptsExecutor.reset();
	m_environment.reset();

	lua_close( m_luaEngine );

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Tools::Core::IMessenger >
PluginInstance::getSystemMessenger() const
{
	return
		getPluginInterface< Tools::Core::IMessenger >(
				Framework::Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Tools::Core::IID_MESSENGER );

} // PluginInstance::getSystemMessenger


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::PluginsManager::ISystemInformation >
PluginInstance::getSystemInformation() const
{
	return
		getPluginInterface< Core::PluginsManager::ISystemInformation >(
				Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Core::PluginsManager::IID_SYSTEM_INFORMATION );

} // PluginInstance::getSystemInformation


/*---------------------------------------------------------------------------*/


void
PluginInstance::exportScriptAPI()
{
	DataExporter exporter = m_exporter->getDataExporter();

	exporter.exportClass< QString >( "QString" )
		->withConstructor()
		.withConstructor< const char* >();

	exporter.exportClass< QPoint  >( "QPoint" )
		->withConstructor()
		.withConstructor< int, int >();

	exporter.exportClass< QSize >( "QSize" )
		->withConstructor()
		.withConstructor< int, int >();

	exporter.exportClass< QRect >( "QRect" )
		->withConstructor()
		.withConstructor< int, int, int, int >();

	exporter.exportClass< Tools::Core::IMessenger >( "IMessenger" )
		->withMethod( "printMessage", ( void ( Tools::Core::IMessenger::* )( const QString& ) )( &Tools::Core::IMessenger::printMessage ) )
		.withMethod(
				"printMessage"
			,	( void ( Tools::Core::IMessenger::* )( const Tools::Core::IMessenger::MessegeLevel::Enum, const QString& ) )( &Tools::Core::IMessenger::printMessage ) )
		.withEnum< Tools::Core::IMessenger::MessegeLevel::Enum >( "MessegeLevel" )
			.withItem( "Info", Tools::Core::IMessenger::MessegeLevel::Info )
			.withItem( "Warning", Tools::Core::IMessenger::MessegeLevel::Warning )
			.withItem( "Error", Tools::Core::IMessenger::MessegeLevel::Error )
			.withItem( "Success", Tools::Core::IMessenger::MessegeLevel::Success );

	exporter.exportVariable( "SystemMessenger", getSystemMessenger().get() );

} // PluginInstance::exportScriptAPI


/*---------------------------------------------------------------------------*/


void
PluginInstance::executeConfigurationScripts()
{
	m_scriptsExecutor->executeFile( m_environment->getSystemConfigDirectory() + "/" + Resources::SystemScriptFileName + Resources::ScriptFileExtension );

} // PluginInstance::executeConfigurationScripts


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
