
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/menu_item/wm_menu_item.hpp"

#include "wm_menu_item.moc"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/


MenuItem::MenuItem(
		const QString& _commandName
	,	const QString& _title
	,	QObject* _parent
	)
	:	QAction( _title, _parent )
	,	m_commandName( _commandName )
{
	connect( this, SIGNAL( changed() ), this, SLOT( onActionStateChanged() ) );

} // MenuItem::MenuItem


/*---------------------------------------------------------------------------*/


MenuItem::~MenuItem()
{
	disconnect( this, SIGNAL( changed() ), this, SLOT( onActionStateChanged() ) );

} // MenuItem::~MenuItem


/*---------------------------------------------------------------------------*/


void
MenuItem::onActionStateChanged()
{
	emit actionWasChanged( m_commandName );

} // MenuItem::onActionToggled


/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
