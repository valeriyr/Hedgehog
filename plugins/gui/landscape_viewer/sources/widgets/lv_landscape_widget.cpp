
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_widget.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"


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
	m_scene->refreshData();

	QGraphicsView::resizeEvent( _event );

} // LandscapeWidget::resizeEvent


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
