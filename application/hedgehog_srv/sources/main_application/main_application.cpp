
#include "hedgehog_srv/sources/ph/hhs_ph.hpp"

#include "hedgehog_srv/sources/main_application/main_application.hpp"
#include "hedgehog_srv/sources/resources/hhs_resources.hpp"

#include "plugins_manager/ih/pm_iloader.hpp"
#include "plugins_manager/h/pm_system_data.hpp"

#include <csignal>

/*---------------------------------------------------------------------------*/

namespace Hedgehog {
namespace Server {

/*---------------------------------------------------------------------------*/


MainApplication::MainApplication( int argc, char* argv[] )
	:	m_qtApplicaiton( argc, argv )
{
	signal(SIGINT, &MainApplication::exitQt);
	signal(SIGTERM, &MainApplication::exitQt);
	signal(SIGBREAK, &MainApplication::exitQt);

} // MainApplication::MainApplication


/*---------------------------------------------------------------------------*/


MainApplication::~MainApplication()
{
} // MainApplication::~MainApplication


/*---------------------------------------------------------------------------*/


int
MainApplication::exec()
{
	Framework::Core::PluginsManager::ILoader::Ptr
		pluginsManagerLoader = Framework::Core::PluginsManager::createLoader();

	QString applicationDirectory( m_qtApplicaiton.applicationDirPath() );

	Framework::Core::PluginsManager::SystemData systemData(
			applicationDirectory + "/" + Resources::PluginsDirectoryName
		,	applicationDirectory + "/" + Resources::ResourcesDirectoryName
		,	applicationDirectory + "/" + Resources::ConfigsDirectoryName
		,	Resources::ApplicationName
		,	Resources::SystemMessengerPluginName
		);

	systemData.m_additionalPluginsDirectories.push_back(
		applicationDirectory + "/" +  Resources::PluginsDirectoryName + "/" + Resources::ServerPluginsDirectoryName );

	pluginsManagerLoader->load( systemData );

	int result = m_qtApplicaiton.exec();

	pluginsManagerLoader->unload();

	return result;

} // MainApplication::exec


/*---------------------------------------------------------------------------*/


void MainApplication::exitQt( int _signal )
{
	QCoreApplication::exit(0);
}


/*---------------------------------------------------------------------------*/

} // namespace Server
} // namespace Hedgehog

/*---------------------------------------------------------------------------*/
