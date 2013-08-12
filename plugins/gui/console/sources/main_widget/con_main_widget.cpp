
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/main_widget/con_main_widget.hpp"

#include "console/sources/resources/con_internal_resources.hpp"

#include "con_main_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


MainWidget::MainWidget()
	:	m_consoleDataView( new QTextEdit( this ) )
	,	m_commandEditor( new QLineEdit( this ) )
{
	m_consoleDataView->setReadOnly( true );

	m_commandEditor->setPlaceholderText( Resources::ConsolePlaceHolderText );

	QVBoxLayout* mainLayout = new QVBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );

	mainLayout->addWidget( m_consoleDataView );
	mainLayout->addWidget( m_commandEditor );

	setLayout( mainLayout );

	QObject::connect( m_commandEditor, SIGNAL( returnPressed() ), this, SLOT( onReturnPressed() ) );

} // MainWidget::MainWidget


/*---------------------------------------------------------------------------*/


MainWidget::~MainWidget()
{
	QObject::disconnect( m_commandEditor, SIGNAL( returnPressed() ), this, SLOT( onReturnPressed() ) );

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
	QString command( m_commandEditor->text() );

	m_commandEditor->clear();

	emit commandWasEntered( command );

} // MainWidget::onReturnPressed


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
