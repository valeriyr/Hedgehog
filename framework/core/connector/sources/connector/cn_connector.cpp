
#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/connector/cn_connector.hpp"

#include "connector/h/cn_plugin_factory.hpp"

#include "connector/sources/plugins_manager/cn_plugins_manager.hpp"
#include "connector/sources/plugins_serializer/cn_plugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/


Connector::Connector()
{
} // Connector::Connector


/*---------------------------------------------------------------------------*/


Connector::~Connector()
{
} // Connector::~Connector


/*---------------------------------------------------------------------------*/


void
Connector::initialize( const std::string& _pluginsDirectory )
{
	m_pluginsManager.reset( new PluginsManager( _pluginsDirectory ) );

	boost::intrusive_ptr< IPluginsSerializer >
		pluginsSerializer( new PluginsSerializer( *m_pluginsManager ) );
	pluginsSerializer->loadPluginsList();

	m_pluginsManager->loadPlugins();

} // Connector::initialize


/*---------------------------------------------------------------------------*/


void
Connector::close()
{
	m_pluginsManager->closePlugins();
	m_pluginsManager.reset();

} // Connector::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

extern "C" __declspec( dllexport )
IConnector*
getConnector()
{
	return new Connector();
}

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
