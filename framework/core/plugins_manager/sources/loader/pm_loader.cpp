
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/loader/pm_loader.hpp"

#include "plugins_manager/sources/resources/pm_internal_resources.hpp"
#include "plugins_manager/sources/plugin/pm_iplugin_instance.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


Loader::Loader()
	:	m_connector()
{
} // Loader::Loader


/*---------------------------------------------------------------------------*/


Loader::~Loader()
{
} // Loader::~Loader


/*---------------------------------------------------------------------------*/


void
Loader::load( const std::string& _pluginsDirectory )
{
	if ( m_connector )
		return;

	typedef IPluginInstance* (*PluginsManagerFactoryPtr) ();

	PluginsManagerFactoryPtr connectorFactory
		= ( PluginsManagerFactoryPtr ) QLibrary::resolve( Resources::LibraryName, Resources::PluginsManagerFactoryName );
	assert( connectorFactory );

	m_connector.reset( connectorFactory() );
	assert( m_connector );

	m_connector->initialize( _pluginsDirectory );

} // Loader::load


/*---------------------------------------------------------------------------*/


void
Loader::unload()
{
	m_connector->close();
	m_connector.reset();

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
