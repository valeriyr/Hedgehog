
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/system_information/pm_system_information.hpp"

#include "iterators/it_simple_iterator.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


SystemInformation::SystemInformation( const SystemData& _systemData )
	:	m_systemData( _systemData )
{
} // SystemInformation::SystemInformation


/*---------------------------------------------------------------------------*/


SystemInformation::~SystemInformation()
{
} // SystemInformation::~SystemInformation


/*---------------------------------------------------------------------------*/


const QString&
SystemInformation::getApplicationDirectory() const
{
	return m_systemData.m_applicationDirectory;

} // SystemInformation::getApplicationDirectory


/*---------------------------------------------------------------------------*/


const QString&
SystemInformation::getPluginsDirectory() const
{
	return m_systemData.m_pluginsDirectory;

} // SystemInformation::getPluginsDirectory


/*---------------------------------------------------------------------------*/


ISystemInformation::AdditionalPluginsDirectoriesIterator
SystemInformation::getAdditionalPluginsDirectories() const
{
	return
		ISystemInformation::AdditionalPluginsDirectoriesIterator(
			new Tools::Core::SimpleIterator< SystemData::AdditionalPluginsDirectoriesCollection >(
				m_systemData.m_additionalPluginsDirectories ) );

} // SystemInformation::getAdditionalPluginsDirectories


/*---------------------------------------------------------------------------*/


const QString&
SystemInformation::getConfigDirectory() const
{
	return m_systemData.m_configDirectory;

} // SystemInformation::getConfigDirectory


/*---------------------------------------------------------------------------*/


const QString&
SystemInformation::getResourcesDirectory() const
{
	return m_systemData.m_resourcesDirectory;

} // SystemInformation::getResourcesDirectory


/*---------------------------------------------------------------------------*/


const QString&
SystemInformation::getApplicationName() const
{
	return m_systemData.m_applicationName;

} // SystemInformation::getApplicationName


/*---------------------------------------------------------------------------*/


const QString&
SystemInformation::getSystemMessengerPluginName() const
{
	return m_systemData.m_systemMessengerPluginName;

} // SystemInformation::getSystemMessengerPluginName


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
