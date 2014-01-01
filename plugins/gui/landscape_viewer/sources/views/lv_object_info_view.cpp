
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
	,	m_showingUnitId( Core::LandscapeModel::IUnit::ms_wrongId )
{
	m_mainWidget->setReadOnly( true );

	setDescriptionForUnit( Core::LandscapeModel::IUnit::ms_wrongId );

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

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::UnitMoved::ms_type
							,	boost::bind( &ObjectInfoView::onUnitMoved, this, _1 ) );

} // ObjectInfoView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	setDescriptionForUnit( Core::LandscapeModel::IUnit::ms_wrongId );

} // ObjectInfoView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onUnitsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	Plugins::Core::LandscapeModel::ILandscape::UnitsCollection selectedUnitsCollection;

	{
		boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
			= m_environment.getCurrentLandscape();

		if ( handle->getLandscape() )
		{
			handle->getLandscape()->fetchSelectedUnits( selectedUnitsCollection );
		}
	}

	setDescriptionForUnit(
			selectedUnitsCollection.empty()
		?	Core::LandscapeModel::IUnit::ms_wrongId
		:	selectedUnitsCollection.front()->getUniqueId() );

} // ObjectInfoView::onUnitsSelectionChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onUnitMoved( const Framework::Core::EventManager::Event& _event )
{
	const Plugins::Core::LandscapeModel::IUnit::IdType unitId
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitMoved::ms_unitIdAttribute ).toInt();

	if ( m_showingUnitId == unitId )
	{
		setDescriptionForUnit( unitId );
	}

} // ObjectInfoView::onUnitMoved


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::setDescriptionForUnit( const Core::LandscapeModel::IUnit::IdType& _unitId )
{
	m_showingUnitId = Core::LandscapeModel::IUnit::ms_wrongId;

	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		boost::intrusive_ptr< Core::LandscapeModel::IUnit > unit = handle->getLandscape()->getUnit( _unitId );

		if ( unit )
		{
			m_showingUnitId = unit->getUniqueId();

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

	if ( m_showingUnitId == Core::LandscapeModel::IUnit::ms_wrongId )
	{
		m_mainWidget->setHtml( Resources::Views::ObjectInfoDefaultText );
	}

} // ObjectInfoView::setDescriptionForUnit


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
