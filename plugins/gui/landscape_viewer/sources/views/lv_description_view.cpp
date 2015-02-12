
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_description_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


DescriptionView::DescriptionView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_descriptionView( new QTextEdit() )
	,	m_viewTitle( Resources::Views::DescriptionViewTitle )
{
	m_descriptionView->setReadOnly( true );

	setDefaultDescription();

} // DescriptionView::DescriptionView


/*---------------------------------------------------------------------------*/


DescriptionView::~DescriptionView()
{
} // DescriptionView::~DescriptionView


/*---------------------------------------------------------------------------*/


const QString&
DescriptionView::getViewTitle() const
{
	return m_viewTitle;

} // DescriptionView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
DescriptionView::getViewWidget()
{
	return m_descriptionView.get();

} // DescriptionView::getViewWidget


/*---------------------------------------------------------------------------*/


void
DescriptionView::viewWasClosed()
{
	m_descriptionView.reset();

} // DescriptionView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
DescriptionView::landscapeWasOpened()
{
	regenerateDescription();

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::VictoryConditionChanged::Type
							,	boost::bind( &DescriptionView::onVictoryConditionChanged, this, _1 ) );

} // DescriptionView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
DescriptionView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();

	setDefaultDescription();

} // DescriptionView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
DescriptionView::regenerateDescription()
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	m_descriptionView->setHtml(
		QString( Resources::Views::LandscapeDescriptionFormat )
			.arg( handle->getLandscapeModel()->getLandscapeFilePath() )
			.arg( handle->getLandscapeModel()->getLandscape()->getWidth() )
			.arg( handle->getLandscapeModel()->getLandscape()->getHeight() )
			.arg( Core::LandscapeModel::VictoryCondition::toString( handle->getLandscapeModel()->getVictoryConditionType() ) )
		);

} // DescriptionView::regenerateDescription


/*---------------------------------------------------------------------------*/


void
DescriptionView::onVictoryConditionChanged( const Framework::Core::EventManager::Event& _event )
{
	regenerateDescription();

} // DescriptionView::onVictoryConditionChanged


/*---------------------------------------------------------------------------*/


void
DescriptionView::setDefaultDescription()
{
	m_descriptionView->setHtml( Resources::Views::LandscapeDescriptionDefaultText );

} // DescriptionView::setDefaultDescription


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
