
#include "minimap_viewer/sources/ph/mv_ph.hpp"

#include "minimap_viewer/sources/minimap_view/mv_minimap_view.hpp"

#include "minimap_viewer/sources/minimap_widget/mv_minimap_widget.hpp"
#include "minimap_viewer/sources/internal_resources/mv_internal_resources.hpp"

#include "minimap_viewer/sources/environment/mv_ienvironment.hpp"

#include "mv_minimap_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

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
MinimapView::showLandscape( const Core::LandscapeModel::ILandscape& _landscape )
{
	m_minimapWidget->showLandscape( _landscape );

} // MinimapView::showLandscape


/*---------------------------------------------------------------------------*/


void
MinimapView::clear()
{
	m_minimapWidget->setDefaultLandscape();

} // MinimapView::clear


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
	m_environment.changeVisibleAreaOnMainWindow( _visibleWidth, _visibleHeight );

} // MinimapView::onVisibilityRectChangedPosition


/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
