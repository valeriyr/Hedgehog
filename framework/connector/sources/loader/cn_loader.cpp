
#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/loader/cn_loader.hpp"

#include "connector/h/cn_plugin_factory.hpp"

#include "connector/sources/resources/cn_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

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
Loader::load()
{
	if ( m_connector )
		return;

	PluginFactoryPtr connectorFactory
		= ( PluginFactoryPtr ) QLibrary::resolve(
				Resources::Internal::LibraryName
			,	PluginFactoryName
			);
	assert( connectorFactory );

	m_connector.reset( connectorFactory() );
	assert( m_connector );

	m_connector->initialize( NULL );

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

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
