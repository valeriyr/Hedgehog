
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
			const QString& _applicationDirectory
		,	const QString& _pluginsDirectory
		,	const QString& _resourcesDirectory
		,	const QString& _configDirectory
		,	const QString& _applicationName
		,	const QString& _systemMessengerPluginName
		)
		:	m_applicationDirectory( _applicationDirectory )
		,	m_pluginsDirectory( _pluginsDirectory )
		,	m_resourcesDirectory( _resourcesDirectory )
		,	m_configDirectory( _configDirectory )
		,	m_applicationName( _applicationName )
		,	m_systemMessengerPluginName( _systemMessengerPluginName )
		,	m_additionalPluginsDirectories()
	{}

/*---------------------------------------------------------------------------*/

	typedef std::vector<QString> AdditionalPluginsDirectoriesCollection;

/*---------------------------------------------------------------------------*/

	QString m_applicationDirectory;

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
