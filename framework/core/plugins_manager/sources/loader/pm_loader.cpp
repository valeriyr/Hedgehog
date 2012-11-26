
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/loader/pm_loader.hpp"

#include "plugins_manager/h/pm_plugin_id.hpp"

#include "plugins_manager/sources/resources/pm_internal_resources.hpp"
#include "plugins_manager/sources/plugin/pm_iplugin_instance.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


Loader::Loader()
	:	m_pluginsManagerComponent()
{
} // Loader::Loader


/*---------------------------------------------------------------------------*/


Loader::~Loader()
{
} // Loader::~Loader


/*---------------------------------------------------------------------------*/


void
Loader::load( const SystemData& _systemData )
{
	if ( m_pluginsManagerComponent )
		return;

	typedef IPluginInstance* (*PluginsManagerFactoryPtr) ();

	PluginsManagerFactoryPtr pluginsManagerFactory
		= ( PluginsManagerFactoryPtr ) QLibrary::resolve( PID_PLUGINS_MANAGER, Resources::PluginsManagerFactoryName );
	assert( pluginsManagerFactory );

	m_pluginsManagerComponent.reset( pluginsManagerFactory() );
	assert( m_pluginsManagerComponent );

	m_pluginsManagerComponent->initialize( _systemData );

} // Loader::load


/*---------------------------------------------------------------------------*/


void
Loader::unload()
{
	m_pluginsManagerComponent->close();
	m_pluginsManagerComponent.reset();

} // Loader::unload


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILoader >
createLoader()
{
	return boost::intrusive_ptr< ILoader >( new Loader() );

} // createLoader


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
