
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/loader/pm_loader.hpp"

#include "plugins_manager/h/pm_plugin_id.hpp"

#include "plugins_manager/sources/resources/pm_internal_resources.hpp"
#include "plugins_manager/sources/component/pm_icomponent_instance.hpp"


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

	typedef IComponentInstance* (*PluginsManagerFactoryPtr) ();

	PluginsManagerFactoryPtr pluginsManagerFactory
		= ( PluginsManagerFactoryPtr ) QLibrary::resolve( PID_PLUGINS_MANAGER, Resources::ComponentFactoryName );
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


ILoader::Ptr
createLoader()
{
	return ILoader::Ptr( new Loader() );

} // createLoader


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
