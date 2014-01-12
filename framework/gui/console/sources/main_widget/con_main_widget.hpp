
#ifndef __CON_MAIN_WIDGET_HPP__
#define __CON_MAIN_WIDGET_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/

class InputWidget;

/*---------------------------------------------------------------------------*/

class MainWidget
	:	public QWidget
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MainWidget();

	virtual ~MainWidget();

/*---------------------------------------------------------------------------*/

	void pushMessage( const QString& _message );

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void commandWasEntered( const QString& _command );

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onReturnPressed();

	void onShowNextCommand();
	void onShowPreviousCommand();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::list< QString >
		CommandsStack;
	typedef
		CommandsStack::iterator
		CommandsStackIterator;

	CommandsStack m_commandsStack;
	CommandsStackIterator m_currentCommand;

	QTextEdit* m_consoleDataView;

	InputWidget* m_inputWidget;

	QMutex m_mutex;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_MAIN_WIDGET_HPP__
