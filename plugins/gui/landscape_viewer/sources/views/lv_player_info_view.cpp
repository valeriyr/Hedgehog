
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_player_info_view.hpp"

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


PlayerInfoView::PlayerInfoView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::PlayerInfoViewTitle )
	,	m_mainWidget( new QTextEdit() )
{
	m_mainWidget->setReadOnly( true );
	m_mainWidget->setFixedHeight( 100 );

	setDefaultText();

} // PlayerInfoView::PlayerInfoView


/*---------------------------------------------------------------------------*/


PlayerInfoView::~PlayerInfoView()
{
} // PlayerInfoView::~PlayerInfoView


/*---------------------------------------------------------------------------*/


const QString&
PlayerInfoView::getViewTitle() const
{
	return m_viewTitle;

} // PlayerInfoView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
PlayerInfoView::getViewWidget()
{
	return m_mainWidget.get();

} // PlayerInfoView::getViewWidget


/*---------------------------------------------------------------------------*/


void
PlayerInfoView::viewWasClosed()
{
	m_mainWidget.reset();

} // PlayerInfoView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
PlayerInfoView::landscapeWasOpened()
{
	updatePlayerInfo();
	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ResourceValueChanged::ms_type
							,	boost::bind( &PlayerInfoView::onResourceValueChanged, this, _1 ) );

} // PlayerInfoView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
PlayerInfoView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	setDefaultText();

} // PlayerInfoView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
PlayerInfoView::onResourceValueChanged( const Framework::Core::EventManager::Event& _event )
{
	updatePlayerInfo();

} // PlayerInfoView::onResourceValueChanged


/*---------------------------------------------------------------------------*/


void
PlayerInfoView::setDefaultText()
{
	m_mainWidget->setHtml( Resources::Views::PlayerInfoDefaultText );

} // PlayerInfoView::setDefaultText


/*---------------------------------------------------------------------------*/


void
PlayerInfoView::updatePlayerInfo()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getPlayer() )
	{
		QString resourcesInfo;

		const Core::LandscapeModel::ResourcesData& resourcesData = handle->getPlayer()->getResourcesData();

		Core::LandscapeModel::ResourcesData::ResourcesDataCollectionConstIterator
				begin = resourcesData.m_data.begin()
			,	end = resourcesData.m_data.end();

		for ( ; begin != end; ++begin )
			resourcesInfo += QString( Resources::Views::PlayerResourceInfoFormat ).arg( begin->first ).arg( begin->second );

		m_mainWidget->setHtml(
			QString( Resources::Views::PlayerInfoTextFormat )
				.arg( handle->getPlayer()->getUniqueId() )
				.arg( resourcesInfo ) );
	}

} // PlayerInfoView::updatePlayerInfo


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
