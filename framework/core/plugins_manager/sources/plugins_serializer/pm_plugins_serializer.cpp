
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/plugins_serializer/pm_plugins_serializer.hpp"

#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "plugins_manager/sources/plugins_manager/pm_iplugins_manager_internal.hpp"
#include "plugins_manager/sources/plugins_manager/pm_plugin_data.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


PluginsSerializer::PluginsSerializer(
		IPluginsManagerInternal& _pluginsManager
	,	const ISystemInformation& _systemInformation
	)
	:	m_pluginsManager( _pluginsManager )
	,	m_systemInformation( _systemInformation )
{
} // PluginsSerializer::PluginsSerializer


/*---------------------------------------------------------------------------*/


PluginsSerializer::~PluginsSerializer()
{
} // PluginsSerializer::~PluginsSerializer


/*---------------------------------------------------------------------------*/


void
PluginsSerializer::loadPluginsList()
{
	QDir pluginsDirectory = QDir( m_systemInformation.getPluginsDirectory().c_str() );
	assert( pluginsDirectory.exists() );

	QStringList filesFilter;
	filesFilter.push_back( "*.dll" );

	QFileInfoList filesList = pluginsDirectory.entryInfoList( filesFilter );

	for ( int i = 0; i < filesList.size(); ++i )
	{
         QFileInfo fileInfo = filesList.at( i );
		 m_pluginsManager.registerPlugin(
			 boost::shared_ptr< PluginData >( new PluginData( fileInfo.baseName().toLocal8Bit().data() ) ) );
	}

} // PluginsSerializer::loadPluginsList


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
