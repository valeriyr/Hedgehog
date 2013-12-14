
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/input_widget/con_input_widget.hpp"

#include "con_input_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


InputWidget::InputWidget( QWidget* _parent )
	:	QLineEdit( _parent )
{
} // InputWidget::InputWidget


/*---------------------------------------------------------------------------*/


InputWidget::~InputWidget()
{
} // InputWidget::~InputWidget


/*---------------------------------------------------------------------------*/


void
InputWidget::keyPressEvent( QKeyEvent* _event )
{
	if ( _event->key() == Qt::Key_Up )
		showPreviousCommand();
	else if ( _event->key() == Qt::Key_Down )
		showNextCommand();
	else
		QLineEdit::keyPressEvent( _event );

} // InputWidget::keyPressEvent


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
