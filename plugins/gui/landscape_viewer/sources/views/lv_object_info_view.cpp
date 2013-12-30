
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_object_info_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_iunit.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

ObjectInfoView::ObjectInfoView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::ObjectInfoViewTitle )
	,	m_mainWidget( new QTextEdit() )
{
	m_mainWidget->setReadOnly( true );

	setDefaultDescription();

} // ObjectInfoView::ObjectInfoView


/*---------------------------------------------------------------------------*/


ObjectInfoView::~ObjectInfoView()
{
} // ObjectInfoView::~ObjectInfoView


/*---------------------------------------------------------------------------*/


const QString&
ObjectInfoView::getViewTitle() const
{
	return m_viewTitle;

} // ObjectInfoView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
ObjectInfoView::getViewWidget()
{
	return m_mainWidget.get();

} // ObjectInfoView::getViewWidget


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::viewWasClosed()
{
	m_mainWidget.reset();

} // ObjectInfoView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::landscapeWasOpened()
{
	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::UnitsSelectionChanged::ms_type
							,	boost::bind( &ObjectInfoView::onUnitsSelectionChanged, this, _1 ) );

} // ObjectInfoView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	setDefaultDescription();

} // ObjectInfoView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onUnitsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	m_mainWidget->clear();

	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		Plugins::Core::LandscapeModel::ILandscape::UnitsCollection selectedUnitsCollection;
		handle->getLandscape()->fetchSelectedUnits( selectedUnitsCollection );

		if ( selectedUnitsCollection.empty() )
		{
			setDefaultDescription();
		}
		else
		{
			boost::intrusive_ptr< Core::LandscapeModel::IUnit > unit = *selectedUnitsCollection.begin();
			m_mainWidget->setHtml(
				QString( Resources::Views::ObjectInfoFormat )
					.arg( unit->getType()->getName() )
					.arg( unit->getHealth() )
					.arg( unit->getType()->getMaximumHealth() )
					.arg( unit->getType()->getMovingSpeed() )
					.arg( unit->getPosition().x() )
					.arg( unit->getPosition().y() )
					.arg( unit->getType()->getObjectSize().width() )
					.arg( unit->getType()->getObjectSize().height() )
					.arg( unit->getUniqueId() ) );
		}
	}

} // ObjectInfoView::onUnitsSelectionChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::setDefaultDescription()
{
	m_mainWidget->setHtml( Resources::Views::ObjectInfoDefaultText );

} // ObjectInfoView::setDefaultDescription


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
