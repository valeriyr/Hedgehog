
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/minimap_widget/le_minimap_widget.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


const QSize MinimapWidget::ms_fixedWidgetSize = QSize( 300, 200 );


/*---------------------------------------------------------------------------*/


MinimapWidget::MinimapWidget(
		const ILandscapeEditorController& _landscapeEditorController
	,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
	,	QWidget* _parent
	)
	:	QGLWidget( QGLFormat( QGL::SampleBuffers ), _parent )
	,	m_landscapeEditorController( _landscapeEditorController )
	,	m_imagesManager( _imagesManager )
	,	m_surfaceLayer( ms_fixedWidgetSize )
{
	setFixedSize( ms_fixedWidgetSize );
	m_surfaceLayer.fill(Qt::white);

} // MinimapWidget::MinimapWidget


/*---------------------------------------------------------------------------*/


MinimapWidget::~MinimapWidget()
{
} // MinimapWidget::~MinimapWidget


/*---------------------------------------------------------------------------*/


void
MinimapWidget::landscapeWasOpened()
{
} // MinimapWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
MinimapWidget::setDefaultLandscape()
{
} // MinimapWidget::setDefaultLandscape


/*---------------------------------------------------------------------------*/


void
MinimapWidget::paintEvent( QPaintEvent* _event )
{
	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surfaceLayer );

} // MinimapWidget::paintEvent


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
