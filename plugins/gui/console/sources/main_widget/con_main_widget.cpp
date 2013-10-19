
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/main_widget/con_main_widget.hpp"

#include "console/sources/resources/con_internal_resources.hpp"
#include "console/sources/input_widget/con_input_widget.hpp"

#include "con_main_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


MainWidget::MainWidget()
	:	m_consoleDataView( new QTextEdit( this ) )
	,	m_inputWidget( new InputWidget( this ) )
	,	m_commandsStack()
	,	m_currentCommand( m_commandsStack.begin() )
{
	m_consoleDataView->setReadOnly( true );

	m_inputWidget->setPlaceholderText( Resources::ConsolePlaceHolderText );

	QVBoxLayout* mainLayout = new QVBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );

	mainLayout->addWidget( m_consoleDataView );
	mainLayout->addWidget( m_inputWidget );

	setLayout( mainLayout );

	QObject::connect( m_inputWidget, SIGNAL( returnPressed() ), this, SLOT( onReturnPressed() ) );
	QObject::connect( m_inputWidget, SIGNAL( showNextCommand() ), this, SLOT( onShowNextCommand() ) );
	QObject::connect( m_inputWidget, SIGNAL( showPreviousCommand() ), this, SLOT( onShowPreviousCommand() ) );

} // MainWidget::MainWidget


/*---------------------------------------------------------------------------*/


MainWidget::~MainWidget()
{
	QObject::disconnect( m_inputWidget, SIGNAL( returnPressed() ), this, SLOT( onReturnPressed() ) );
	QObject::disconnect( m_inputWidget, SIGNAL( showNextCommand() ), this, SLOT( onShowNextCommand() ) );
	QObject::disconnect( m_inputWidget, SIGNAL( showPreviousCommand() ), this, SLOT( onShowPreviousCommand() ) );

} // MainWidget::~MainWidget


/*---------------------------------------------------------------------------*/


void
MainWidget::pushMessage( const QString& _message )
{
	m_consoleDataView->append( _message );

} // MainWidget::pushMessage


/*---------------------------------------------------------------------------*/


void
MainWidget::onReturnPressed()
{
	QString command( m_inputWidget->text() );

	m_commandsStack.push_back( command );
	m_currentCommand = --( m_commandsStack.end() );

	m_inputWidget->clear();

	emit commandWasEntered( command );

} // MainWidget::onReturnPressed


/*---------------------------------------------------------------------------*/


void
MainWidget::onShowNextCommand()
{
	if ( m_commandsStack.empty() )
		return;

	if (	m_inputWidget->text() == *m_currentCommand
		&&	m_currentCommand != --( m_commandsStack.end() ) )
	{
		++m_currentCommand;
	}

	m_inputWidget->setText( *m_currentCommand );

} // MainWidget::onShowNextCommand


/*---------------------------------------------------------------------------*/


void
MainWidget::onShowPreviousCommand()
{
	if ( m_commandsStack.empty() )
		return;

	if (	m_inputWidget->text() == *m_currentCommand
		&&	m_currentCommand != m_commandsStack.begin() )
	{
		--m_currentCommand;
	}

	m_inputWidget->setText( *m_currentCommand );

} // MainWidget::onShowPreviousCommand


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
