
#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugin/cn_plugin_instance.hpp"

#include "connector/h/cn_plugin_factory.hpp"

#include "connector/sources/plugins_manager/cn_plugins_manager.hpp"
#include "connector/sources/plugins_serializer/cn_plugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE( PM_INTERFACE_ID, getPluginsManager().get() );

END_INTERFACE_MAP()


/*---------------------------------------------------------------------------*/


PluginInstance::PluginInstance()
{
} // PluginInstance::PluginInstance


/*---------------------------------------------------------------------------*/


PluginInstance::~PluginInstance()
{
} // PluginInstance::~PluginInstance


/*---------------------------------------------------------------------------*/


void
PluginInstance::initialize( IBase* _connector )
{
	m_pluginsManager.reset( new PluginsManager() );

	boost::intrusive_ptr< IPluginsSerializer >
		pluginsSerializer( new PluginsSerializer( *m_pluginsManager ) );
	pluginsSerializer->loadPluginsList();

	m_pluginsManager->loadPlugins();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_pluginsManager->closePlugins();
	m_pluginsManager.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPluginsManager >
PluginInstance::getPluginsManager() const
{
	return m_pluginsManager;

} // PluginInstance::getPluginsManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
