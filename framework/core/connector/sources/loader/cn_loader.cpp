
#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/loader/cn_loader.hpp"

#include "connector/sources/resources/cn_internal_resources.hpp"
#include "connector/sources/connector/cn_iconnector.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
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
Loader::load( const std::string& _pluginsDirectory )
{
	if ( m_connector )
		return;

	typedef IConnector* (*ConnectorFactoryPtr) ();

	ConnectorFactoryPtr connectorFactory
		= ( ConnectorFactoryPtr ) QLibrary::resolve( Resources::LibraryName, Resources::ConnectorFactoryName );
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

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
