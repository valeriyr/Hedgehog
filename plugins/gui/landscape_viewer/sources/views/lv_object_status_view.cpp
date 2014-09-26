
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_object_status_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/ih/components/lm_itrain_component.hpp"

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
	,	m_builderId( Tools::Core::Generators::IGenerator::ms_wrongId )
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
							,	Plugins::Core::LandscapeModel::Events::TrainQueueChanged::ms_type
							,	boost::bind( &ObjectStatusView::onTrainQueueChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::TrainProgressChanged::ms_type
							,	boost::bind( &ObjectStatusView::onTrainProgressChanged, this, _1 ) );

} // ObjectStatusView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	clearBuildQueue();
	clearProgressLabel();

} // ObjectStatusView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscapeModel()->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		m_builderId = Tools::Core::Generators::IGenerator::ms_wrongId;

		if (	!selectedObjectsCollection.empty()
			&&	( *selectedObjectsCollection.begin() )->getComponent< Core::LandscapeModel::ITrainComponent >( Core::LandscapeModel::ComponentId::Train )
			&&	( handle->getLandscapeModel()->getGameModeType() == Core::LandscapeModel::IGameMode::Type::Replay
			||	handle->getLandscapeModel()->isMyObject( *selectedObjectsCollection.begin() ) ) )
		{
			m_builderId = ( *selectedObjectsCollection.begin() )->getUniqueId();
		}
	}

	updateBuildQueue();
	updateProgressLabel();

} // ObjectStatusView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::onTrainQueueChanged( const Framework::Core::EventManager::Event& _event )
{
	if ( m_builderId == _event.getAttribute( Core::LandscapeModel::Events::TrainQueueChanged::ms_trainerIdAttribute ).toInt() )
		updateBuildQueue();

} // ObjectStatusView::onTrainQueueChanged


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::onTrainProgressChanged( const Framework::Core::EventManager::Event& _event )
{
	if ( m_builderId == _event.getAttribute( Core::LandscapeModel::Events::TrainProgressChanged::ms_trainerIdAttribute ).toInt() )
	{
		Core::LandscapeModel::TickType progress = _event.getAttribute( Core::LandscapeModel::Events::TrainProgressChanged::ms_trainerProgressAttribute ).toLongLong();
		Core::LandscapeModel::TickType total = _event.getAttribute( Core::LandscapeModel::Events::TrainProgressChanged::ms_creationTimeAttribute ).toLongLong();

		updateProgressLabel( static_cast< float >( progress ) / total * 100 );
	}

} // ObjectStatusView::onTrainProgressChanged


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::updateBuildQueue()
{
	clearBuildQueue();

	if ( m_builderId != Tools::Core::Generators::IGenerator::ms_wrongId )
	{
		boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
			= m_environment.lockModel();

		if ( handle->getLandscapeModel()->getLandscape() )
		{
			boost::shared_ptr< Core::LandscapeModel::Object > object
				= handle->getLandscapeModel()->getLandscape()->getObject( m_builderId );

			Core::LandscapeModel::ILandscapeModel::TrainObjectsList trainObjectsList;
			handle->getLandscapeModel()->getTrainObjectsList( object, trainObjectsList );

			if ( !trainObjectsList.empty() )
			{
				m_currentObject->setIcon( QIcon( m_environment.getPixmap( *trainObjectsList.begin() ) ) );

				Core::LandscapeModel::ILandscapeModel::TrainObjectsListIterator
						begin = trainObjectsList.begin()
					,	end = trainObjectsList.end();

				++begin;

				for ( ; begin != end; ++begin )
				{
					QListWidgetItem* listItem = new QListWidgetItem();

					listItem->setIcon( QIcon( m_environment.getPixmap( *begin ) ) );

					m_listWidget->addItem( listItem );
				}
			}
			else
			{
				clearProgressLabel();
			}
		}
	}

} // ObjectStatusView::updateBuildQueue


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::updateProgressLabel( const int _progress )
{
	m_label->setText( QString( "Built: %1 %" ).arg( _progress ) );

} // ObjectStatusView::updateProgressLabel


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::updateProgressLabel()
{
	clearProgressLabel();

	if ( m_builderId != Tools::Core::Generators::IGenerator::ms_wrongId )
	{
		boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
			= m_environment.lockModel();

		if ( handle->getLandscapeModel()->getLandscape() )
		{
			boost::shared_ptr< Core::LandscapeModel::Object > object
				= handle->getLandscapeModel()->getLandscape()->getObject( m_builderId );

			boost::intrusive_ptr< Core::LandscapeModel::ITrainComponent > trainComponent
				= object->getComponent< Core::LandscapeModel::ITrainComponent >( Core::LandscapeModel::ComponentId::Train );

			m_label->setText( QString( "Built: %1 %" ).arg( static_cast< int >( trainComponent->getTrainData().m_trainProgress * 100 ) ) );
		}
	}

} // ObjectStatusView::updateProgressLabel


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::clearBuildQueue()
{
	m_currentObject->setIcon( QIcon() );
	m_listWidget->clear();

} // ObjectStatusView::clearBuildQueue


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::clearProgressLabel()
{
	m_label->clear();

} // ObjectStatusView::clearProgressLabel


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
