
#ifndef __PM_SYSTEM_DATA_HPP__
#define __PM_SYSTEM_DATA_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct SystemData
{

/*---------------------------------------------------------------------------*/

	SystemData(
			const QString& _pluginsDirectory
		,	const QString& _resourcesDirectory
		,	const QString& _configDirectory
		,	const QString& _applicationName
		,	const QString& _systemMessengerPluginName
		)
		:	m_pluginsDirectory( _pluginsDirectory )
		,	m_resourcesDirectory( _resourcesDirectory )
		,	m_configDirectory( _configDirectory )
		,	m_applicationName( _applicationName )
		,	m_systemMessengerPluginName( _systemMessengerPluginName )
		,	m_additionalPluginsDirectories()
	{}

/*---------------------------------------------------------------------------*/

	SystemData( const SystemData& _systemData )
	{
		*this = _systemData;
	}

/*---------------------------------------------------------------------------*/

	SystemData& operator= ( const SystemData& _systemData )
	{
		m_pluginsDirectory = _systemData.m_pluginsDirectory;
		m_resourcesDirectory = _systemData.m_resourcesDirectory;
		m_configDirectory = _systemData.m_configDirectory;
		m_applicationName = _systemData.m_applicationName;
		m_systemMessengerPluginName = _systemData.m_systemMessengerPluginName;
		m_additionalPluginsDirectories = _systemData.m_additionalPluginsDirectories;

		return *this;
	}

/*---------------------------------------------------------------------------*/

	typedef std::vector<QString> AdditionalPluginsDirectoriesCollection;

/*---------------------------------------------------------------------------*/

	QString m_pluginsDirectory;

	QString m_resourcesDirectory;

	QString m_configDirectory;

	QString m_applicationName;

	QString m_systemMessengerPluginName;

	AdditionalPluginsDirectoriesCollection m_additionalPluginsDirectories;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_SYSTEM_DATA_HPP__
