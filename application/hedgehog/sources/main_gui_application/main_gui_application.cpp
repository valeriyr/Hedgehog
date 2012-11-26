
#include "hedgehog/sources/ph/hh_ph.hpp"

#include "hedgehog/sources/main_gui_application/main_gui_application.hpp"
#include "hedgehog/sources/resources/hh_resources.hpp"

#include "plugins_manager/ih/pm_iloader.hpp"
#include "plugins_manager/h/pm_system_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Hedgehog {

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
	boost::intrusive_ptr< Framework::Core::PluginsManager::ILoader >
		pluginsManagerLoader = Framework::Core::PluginsManager::createLoader();

	std::string pluginsDirectory( m_qtApplicaiton.applicationDirPath().toLocal8Bit().data() );
	pluginsDirectory += "/";
	pluginsDirectory += Resources::PluginsDirectoryName;

	Framework::Core::PluginsManager::SystemData systemData(
			pluginsDirectory + "/" + Resources::PluginsDirectoryName
		,	pluginsDirectory + "/" + Resources::ResourcesDirectoryName
		,	pluginsDirectory + "/" + Resources::ConfigsDirectoryName
		,	Resources::ApplicationName
		);

	pluginsManagerLoader->load( systemData );

	int result = m_qtApplicaiton.exec();

	pluginsManagerLoader->unload();

	return result;

} // MainGuiApplication::exec


/*---------------------------------------------------------------------------*/

} // namespace Hedgehog

/*---------------------------------------------------------------------------*/
