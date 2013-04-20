
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/menu_item/wm_menu_item.hpp"

#include "window_manager/sources/environment/wm_ienvironment.hpp"

#include "commands_manager/ih/cm_icommand_executor.hpp"

#include "wm_menu_item.moc"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/


MenuItem::MenuItem(
		const QString& _commandName
	,	const QString& _title
	,	IEnvironment& _environment
	,	QObject* _parent
	)
	:	QAction( _title, _parent )
	,	m_commandName( _commandName )
	,	m_environment( _environment )
{
	connect( this, SIGNAL( triggered(bool) ), this, SLOT( onActionStateChanged() ) );

} // MenuItem::MenuItem


/*---------------------------------------------------------------------------*/


MenuItem::~MenuItem()
{
	disconnect( this, SIGNAL( triggered(bool) ), this, SLOT( onActionStateChanged() ) );

} // MenuItem::~MenuItem


/*---------------------------------------------------------------------------*/


void
MenuItem::onActionStateChanged()
{
	emit actionWasChanged( m_commandName );

	try
	{
		m_environment.getCommandExecutor()->executeCommand( m_commandName );
		//printMessage( _command );
	}
	catch( const std::exception& /*_exception*/ )
	{
		/*printMessage(
				Tools::Core::IMessenger::MessegeLevel::Error
			,	QString( Resources::SyntaxErrorMessageFormat ).arg( _command ) );*/
	}

} // MenuItem::onActionToggled


/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
