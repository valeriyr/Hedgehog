
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/system_information/pm_system_information.hpp"


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
SystemInformation::getPluginsDirectory() const
{
	return m_systemData.m_pluginsDirectory;

} // SystemInformation::getPluginsDirectory


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

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
