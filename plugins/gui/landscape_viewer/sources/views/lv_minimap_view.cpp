
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_minimap_view.hpp"

#include "landscape_viewer/sources/widgets/lv_minimap_widget.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "lv_minimap_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


MinimapView::MinimapView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_minimapWidget( new MinimapWidget( _environment ) )
	,	m_viewTitle( Resources::Views::MinimapViewTitle )
{
	QObject::connect(
			m_minimapWidget.get()
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	this
		,	SLOT( onVisibilityRectChangedPosition( const float, const float ) ) );

} // MinimapView::MinimapView


/*---------------------------------------------------------------------------*/


MinimapView::~MinimapView()
{
	QObject::disconnect(
			m_minimapWidget.get()
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	this
		,	SLOT( onVisibilityRectChangedPosition( const float, const float ) ) );

} // MinimapView::~MinimapView


/*---------------------------------------------------------------------------*/


const QString&
MinimapView::getViewTitle() const
{
	return m_viewTitle;

} // MinimapView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
MinimapView::getViewWidget()
{
	return m_minimapWidget.get();

} // MinimapView::getViewWidget


/*---------------------------------------------------------------------------*/


void
MinimapView::viewWasClosed()
{
	m_minimapWidget.reset();

} // MinimapView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
MinimapView::landscapeWasOpened( const Core::LandscapeModel::ILandscape& _landscape )
{
	m_minimapWidget->showLandscape( _landscape );

} // MinimapView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
MinimapView::landscapeWasClosed()
{
	m_minimapWidget->setDefaultLandscape();

} // MinimapView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
MinimapView::setVisibilityRectSize( const float _relVisibleWidth, const float _relVisibleHeight )
{
	m_minimapWidget->setVisibilityRectSize( _relVisibleWidth, _relVisibleHeight );

} // MinimapView::setVisibilityRectSize


/*---------------------------------------------------------------------------*/


void
MinimapView::setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight )
{
	m_minimapWidget->setVisibilityRectPosition( _relVisibleWidth, _relVisibleHeight );

} // MinimapView::setVisibilityRectPosition


/*---------------------------------------------------------------------------*/


void
MinimapView::onVisibilityRectChangedPosition( const float _visibleWidth, const float _visibleHeight )
{
	//m_environment.changeVisibleAreaOnMainWindow( _visibleWidth, _visibleHeight );

} // MinimapView::onVisibilityRectChangedPosition


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
