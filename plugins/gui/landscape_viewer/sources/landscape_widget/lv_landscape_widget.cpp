
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/landscape_widget/lv_landscape_widget.hpp"

#include "landscape_viewer/sources/landscape_scene/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"

// #include "lv_landscape_widget.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeWidget::LandscapeWidget(
		const IEnvironment& _environment
	,	LandscapeScene* _scene
	,	QWidget* _parent
	)
	:	QGraphicsView( _scene, _parent )
	,	m_environment( _environment )
	,	m_scene( _scene )
{
} // LandscapeWidget::LandscapeWidget


/*---------------------------------------------------------------------------*/


LandscapeWidget::~LandscapeWidget()
{
} // LandscapeWidget::~LandscapeWidget


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::resizeEvent( QResizeEvent* _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
		landscape = m_environment.getLandscape();

	if ( landscape )
		m_scene->showLandscape( *landscape );

	QGraphicsView::resizeEvent( _event );

} // LandscapeWidget::resizeEvent


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
