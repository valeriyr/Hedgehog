
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/menu_item/wm_menu_item.hpp"

#include "window_manager/sources/environment/wm_ienvironment.hpp"

#include "commands_manager/ih/cm_icommand_executor.hpp"
#include "commands_manager/ih/cm_iexceptions.hpp"

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
	try
	{
		m_environment.getCommandExecutor()->executeCommand( m_commandName );
	}
	catch( const Framework::Core::CommandsManager::IException& /*_exception*/ )
	{
		assert( !"Some exception during command execution from menu!" );
	}

} // MenuItem::onActionToggled


/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
