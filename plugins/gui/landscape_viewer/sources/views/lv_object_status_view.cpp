
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_object_status_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


ObjectStatusView::ObjectStatusView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::ObjectStatusViewTitle )
	,	m_mainWidget( new QWidget() )
	,	m_builderId( Core::LandscapeModel::Object::ms_wrongId )
{
	m_listWidget = new QListWidget();
	m_label = new QLabel();
	m_currentObject = new QPushButton();

	QHBoxLayout* currentObjectLayout = new QHBoxLayout();

	currentObjectLayout->addWidget( m_currentObject );
	currentObjectLayout->addWidget( m_label );

	QVBoxLayout* mainLayout = new QVBoxLayout();

	mainLayout->addLayout( currentObjectLayout );
	mainLayout->addWidget( m_listWidget );
	
	m_mainWidget->setLayout( mainLayout );

	m_listWidget->setViewMode( QListView::IconMode );

	m_currentObject->setFixedSize( QSize( 32, 32 ) );
	m_currentObject->setIconSize( QSize( 32, 32 ) );

} // ObjectStatusView::ObjectStatusView


/*---------------------------------------------------------------------------*/


ObjectStatusView::~ObjectStatusView()
{
} // ObjectStatusView::~ObjectStatusView


/*---------------------------------------------------------------------------*/


const QString&
ObjectStatusView::getViewTitle() const
{
	return m_viewTitle;

} // ObjectStatusView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
ObjectStatusView::getViewWidget()
{
	return m_mainWidget.get();

} // ObjectStatusView::getViewWidget


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::viewWasClosed()
{
	m_mainWidget.reset();

} // ObjectStatusView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::landscapeWasOpened()
{
	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectsSelectionChanged::ms_type
							,	boost::bind( &ObjectStatusView::onObjectsSelectionChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::BuilderQueueChanged::ms_type
							,	boost::bind( &ObjectStatusView::onBuilderQueueChanged, this, _1 ) );

} // ObjectStatusView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	clear();

} // ObjectStatusView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		m_builderId = Core::LandscapeModel::Object::ms_wrongId;

		if (	!selectedObjectsCollection.empty()
			&&	( *selectedObjectsCollection.begin() )->getComponent< Core::LandscapeModel::IBuilderComponent >( Core::LandscapeModel::ComponentId::Builder ) )
		{
			m_builderId = ( *selectedObjectsCollection.begin() )->getUniqueId();
		}
	}

	updateBuildQueue();

} // ObjectStatusView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::onBuilderQueueChanged( const Framework::Core::EventManager::Event& _event )
{
	if ( m_builderId == _event.getAttribute( Core::LandscapeModel::Events::BuilderQueueChanged::ms_builderIdAttribute ).toInt() )
		updateBuildQueue();

} // ObjectStatusView::onBuilderQueueChanged


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::updateBuildQueue()
{
	clear();

	if ( m_builderId != Core::LandscapeModel::Object::ms_wrongId )
	{
		boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
			= m_environment.getCurrentLandscape();

		if ( handle->getLandscape() )
		{
			boost::shared_ptr< Core::LandscapeModel::Object > object = handle->getLandscape()->getObject( m_builderId );

			boost::intrusive_ptr< Core::LandscapeModel::IBuilderComponent > builderComponent
				= object->getComponent< Core::LandscapeModel::IBuilderComponent >( Core::LandscapeModel::ComponentId::Builder );

			m_label->setText( QString( "Built: %1 %" ).arg( builderComponent->getBuildData().m_buildProgress ) );

			if ( !builderComponent->getBuildData().m_buildQueue.empty() )
			{
				m_currentObject->setIcon( QIcon( m_environment.getPixmap( *builderComponent->getBuildData().m_buildQueue.begin() ) ) );

				Core::LandscapeModel::IBuilderComponent::BuildData::BuildObjectsQueueIterator
						begin = builderComponent->getBuildData().m_buildQueue.begin()
					,	end = builderComponent->getBuildData().m_buildQueue.end();

				++begin;

				for ( ; begin != end; ++begin )
				{
					QListWidgetItem* listItem = new QListWidgetItem();

					listItem->setIcon( QIcon( m_environment.getPixmap( *begin ) ) );

					m_listWidget->addItem( listItem );
				}
			}
		}
	}

} // ObjectStatusView::updateBuildQueue


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::clear()
{
	m_currentObject->setIcon( QIcon() );
	m_listWidget->clear();
	m_label->clear();

} // ObjectStatusView::clear


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
