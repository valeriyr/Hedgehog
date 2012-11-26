
#include "hedgehog/sources/ph/hh_ph.hpp"

#include "hedgehog/sources/main_gui_application/main_gui_application.hpp"
#include "hedgehog/sources/resources/hh_resources.hpp"

#include "plugins_manager/ih/pm_iloader.hpp"


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
		connectorLoader = Framework::Core::PluginsManager::createLoader();

	std::string pluginsDirectory( m_qtApplicaiton.applicationDirPath().toLocal8Bit().data() );
	pluginsDirectory += "/";
	pluginsDirectory += Resources::PluginsDirectoryName;

	connectorLoader->load( pluginsDirectory );

	int result = m_qtApplicaiton.exec();

	connectorLoader->unload();

	return result;

} // MainGuiApplication::exec


/*---------------------------------------------------------------------------*/

} // namespace Hedgehog

/*---------------------------------------------------------------------------*/
