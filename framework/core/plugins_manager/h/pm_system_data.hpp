
#ifndef __PM_SYSTEM_DATA_HPP__
#define __PM_SYSTEM_DATA_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct SystemData
{
	SystemData(
			const std::string& _pluginsDirectory
		,	const std::string& _resourcesDirectory
		,	const std::string& _configDirectory
		,	const std::string& _applicationName
		)
		:	m_pluginsDirectory( _pluginsDirectory )
		,	m_resourcesDirectory( _resourcesDirectory )
		,	m_configDirectory( _configDirectory )
		,	m_applicationName( _applicationName )
	{}

	SystemData( const SystemData& _systemData )
	{
		*this = _systemData;
	}

	SystemData& operator= ( const SystemData& _systemData )
	{
		m_pluginsDirectory = _systemData.m_pluginsDirectory;
		m_resourcesDirectory = _systemData.m_resourcesDirectory;
		m_configDirectory = _systemData.m_configDirectory;
		m_applicationName = _systemData.m_applicationName;

		return *this;
	}

	std::string m_pluginsDirectory;

	std::string m_resourcesDirectory;

	std::string m_configDirectory;

	std::string m_applicationName;
};


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_SYSTEM_DATA_HPP__
