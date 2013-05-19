
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_landscape_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"
#include "landscape_viewer/sources/widgets/lv_landscape_widget.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeView::LandscapeView( const IEnvironment& _environment, QObject* _parent )
	:	QObject( _parent )
	,	m_environment( _environment )
	,	m_viewTitle( Resources::Views::LandscapeViewTitle )
	,	m_landscapeScene( new LandscapeScene( _environment ) )
	,	m_landscapeWidget( new LandscapeWidget( _environment, m_landscapeScene.get() ) )
{
} // LandscapeView::LandscapeView


/*---------------------------------------------------------------------------*/


LandscapeView::~LandscapeView()
{
} // LandscapeView::~LandscapeView


/*---------------------------------------------------------------------------*/


const QString&
LandscapeView::getViewTitle() const
{
	return m_viewTitle;

} // LandscapeView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
LandscapeView::getViewWidget()
{
	return m_landscapeWidget.get();

} // LandscapeView::getViewWidget


/*---------------------------------------------------------------------------*/


void
LandscapeView::viewWasClosed()
{
	m_landscapeWidget.reset();
	m_landscapeScene.reset();

} // LandscapeView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
LandscapeView::showCurrentLandscape()
{
	if ( m_environment.getLandscape() )
	{
		m_landscapeScene->showLandscape( *m_environment.getLandscape() );
	}

} // LandscapeView::showCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeView::clearView()
{
	m_landscapeScene->clear();
	m_landscapeScene->setSceneRect( 0, 0, 0, 0 );

} // LandscapeView::clearView


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
