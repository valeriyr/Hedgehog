
#include "hedgehog/sources/ph/hh_ph.hpp"

#include "hedgehog/sources/main_gui_application/main_gui_application.hpp"
#include "hedgehog/sources/resources/hh_resources.hpp"

#include "plugins_manager/ih/pm_iloader.hpp"
#include "plugins_manager/h/pm_system_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Hedgehog {
namespace Client {

/*---------------------------------------------------------------------------*/


MainGuiApplication::MainGuiApplication( int argc, char* argv[] )
	:	m_qtApplicaiton( argc, argv )
{
} // MainGuiApplication::MainGuiApplication


/*---------------------------------------------------------------------------*/


MainGuiApplication::~MainGuiApplication()
{
} // MainGuiApplication::~MainGuiApplication


/*---------------------------------------------------------------------------*/


int
MainGuiApplication::exec()
{
	Framework::Core::PluginsManager::ILoader::Ptr
		pluginsManagerLoader = Framework::Core::PluginsManager::createLoader();

	QString applicationDirectory( m_qtApplicaiton.applicationDirPath() );

	Framework::Core::PluginsManager::SystemData systemData(
			applicationDirectory
		,	applicationDirectory + "/" + Resources::PluginsDirectoryName
		,	applicationDirectory + "/" + Resources::ResourcesDirectoryName
		,	applicationDirectory + "/" + Resources::ConfigsDirectoryName
		,	Resources::ApplicationName
		,	Resources::SystemMessengerPluginName
		);

	systemData.m_additionalPluginsDirectories.push_back(
		applicationDirectory + "/" +  Resources::PluginsDirectoryName + "/" + Resources::ClientPluginsDirectoryName );

	pluginsManagerLoader->load( systemData );

	int result = m_qtApplicaiton.exec();

	pluginsManagerLoader->unload();

	return result;

} // MainGuiApplication::exec


/*---------------------------------------------------------------------------*/

} // namespace Client
} // namespace Hedgehog

/*---------------------------------------------------------------------------*/
