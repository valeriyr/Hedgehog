
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_widget/le_landscape_widget.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeWidget::LandscapeWidget(
		const ILandscapeEditorController& _landscapeEditorController
	,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
	,	QWidget* _parent
	)
	:	QGLWidget( QGLFormat( QGL::SampleBuffers ), _parent )
	,	m_landscapeEditorController( _landscapeEditorController )
	,	m_imagesManager( _imagesManager )
	,	m_surfaceLayer()
	,	m_objectsLayer()
{
	setDefaultLandscape();

} // LandscapeWidget::LandscapeWidget


/*---------------------------------------------------------------------------*/


LandscapeWidget::~LandscapeWidget()
{
} // LandscapeWidget::~LandscapeWidget


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::landscapeWasOpened()
{
	regenerate();

	setVisible( true );

} // LandscapeWidget::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::setDefaultLandscape()
{
	setVisible( false );
	setFixedSize( 0, 0 );

} // LandscapeWidget::setDefaultLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::mouseDoubleClickEvent ( QMouseEvent* _event )
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	const unsigned int width = _event->pos().x() / Resources::Landscape::CellSize;
	const unsigned int height = _event->pos().y() / Resources::Landscape::CellSize;

	switch( landscape->getSurfaceItem( width, height ) )
	{
	case Plugins::Core::LandscapeModel::SurfaceItems::Grass:
		landscape->setSurfaceItem( width, height, Plugins::Core::LandscapeModel::SurfaceItems::Snow );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Snow:
		landscape->setSurfaceItem( width, height, Plugins::Core::LandscapeModel::SurfaceItems::Water );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Water:
		landscape->setSurfaceItem( width, height, Plugins::Core::LandscapeModel::SurfaceItems::Grass );
		break;
	default:
		assert( !"Unrecognized surface item" );
		break;
	}

	QPainter painter;
	painter.begin( &m_surfaceLayer );
	painter.setRenderHint( QPainter::Antialiasing );

	drawSurfaceItem( painter, width, height );

	update();

} // LandscapeWidget::mouseDoubleClickEvent


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::paintEvent( QPaintEvent* _event )
{
	QPainter painter;
	painter.begin( this );
	painter.drawPixmap( 0, 0, m_surfaceLayer );
	painter.drawPixmap( 0, 0, m_objectsLayer );

} // LandscapeWidget::paintEvent


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerate()
{
	regenerateSurfaceLayer();
	regenerateObjectsLayer();

	setFixedSize( m_surfaceLayer.size() );

} // LandscapeWidget::regenerate


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerateSurfaceLayer()
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	m_surfaceLayer
		= QPixmap( QSize(
				landscape->getWidth() * Resources::Landscape::CellSize
			,	landscape->getHeight() * Resources::Landscape::CellSize ) );

	QPainter painter;
	painter.begin( &m_surfaceLayer );
	painter.setRenderHint( QPainter::Antialiasing );

	for ( unsigned int i = 0; i < landscape->getWidth(); ++i )
		for ( unsigned int j = 0; j < landscape->getHeight(); ++j )
			drawSurfaceItem( painter, i, j );

	/*for ( unsigned int i = 0; i < landscape->getWidth(); ++i )
		painter.drawLine(
				i * Resources::Landscape::CellSize
			,	0
			,	i * Resources::Landscape::CellSize
			,	m_surfaceLayer.size().height() );

	for ( unsigned int i = 0; i < landscape->getHeight(); ++i )
		painter.drawLine(
				0
			,	i * Resources::Landscape::CellSize
			,	m_surfaceLayer.size().width()
			,	i * Resources::Landscape::CellSize );*/

} // LandscapeWidget::regenerateSurfaceLayer


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::regenerateObjectsLayer()
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	m_objectsLayer
		= QPixmap( QSize(
				landscape->getWidth() * Resources::Landscape::CellSize
			,	landscape->getHeight() * Resources::Landscape::CellSize ) );
	m_objectsLayer.fill( Qt::transparent );

	QPainter painter;
	painter.begin( &m_objectsLayer );
	painter.setRenderHint( QPainter::Antialiasing );

	QBrush surfaceItemBrash( QColor( 111, 111, 111 ) );
	painter.fillRect(
			QRect(
					3 * Resources::Landscape::CellSize
				,	3 * Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize )
		, surfaceItemBrash );

} // LandscapeWidget::regenerateObjectsLayer


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::drawSurfaceItem(
		QPainter& _painter
	,	const unsigned int _widthIndex
	,	const unsigned int _heightIndex )
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	Plugins::Core::LandscapeModel::SurfaceItems::Enum
		surfaceItem = landscape->getSurfaceItem( _widthIndex, _heightIndex );

	QColor color;

	switch( surfaceItem )
	{
	case Plugins::Core::LandscapeModel::SurfaceItems::Grass:
		color.setRgb( 50, 200, 100 );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Snow:
		color.setRgb( 155, 255, 255 );
		break;
	case Plugins::Core::LandscapeModel::SurfaceItems::Water:
		color.setRgb( 0, 120, 245 );
		break;
	default:
		assert( !"Unrecognized surface item" );
		break;
	}

	if ( surfaceItem == Plugins::Core::LandscapeModel::SurfaceItems::Grass)
	{
		QString grassImagePath( "grass%1" );
		int grassNamber = ( rand() % 8 ) + 1;
		if ( grassNamber > 3 )
			grassNamber = 1;

		_painter.drawPixmap(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize )
				,	m_imagesManager.getPixmap( grassImagePath.arg( grassNamber ) ) );
	}
	else if ( surfaceItem == Plugins::Core::LandscapeModel::SurfaceItems::Water )
	{
		drawWater( _painter, _widthIndex, _heightIndex );
	}
	else
	{
		QBrush surfaceItemBrash( color );
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize )
			, surfaceItemBrash );
	}

	// top
	if ( ( _heightIndex != 0 ) && ( landscape->getSurfaceItem( _widthIndex, _heightIndex - 1 )  == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _painter, _widthIndex, _heightIndex - 1 );

	// bottom
	if ( ( _heightIndex != landscape->getHeight() - 1 ) && ( landscape->getSurfaceItem( _widthIndex, _heightIndex + 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _painter, _widthIndex, _heightIndex + 1 );

	// left
	if ( ( _widthIndex != 0 ) && ( landscape->getSurfaceItem( _widthIndex - 1, _heightIndex ) == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _painter, _widthIndex - 1, _heightIndex );

	// right
	if ( ( _widthIndex != landscape->getWidth() - 1 ) && ( landscape->getSurfaceItem( _widthIndex + 1, _heightIndex ) == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _painter, _widthIndex + 1, _heightIndex );

	// left top
	if (	( _widthIndex != 0  && _heightIndex != 0 )
		&& landscape->getSurfaceItem( _widthIndex - 1, _heightIndex - 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _painter, _widthIndex - 1, _heightIndex - 1 );

	// right bottom
	if (	( ( _widthIndex != landscape->getWidth() - 1 )  && ( _heightIndex != landscape->getHeight() - 1 ) )
		&& landscape->getSurfaceItem( _widthIndex + 1, _heightIndex + 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _painter, _widthIndex + 1, _heightIndex + 1 );

	// right top
	if (	( ( _widthIndex != landscape->getWidth() - 1 )  && ( _heightIndex != 0 ) )
		&& landscape->getSurfaceItem( _widthIndex + 1, _heightIndex - 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _painter, _widthIndex + 1, _heightIndex - 1 );

	// left bottom
	if (	( ( _widthIndex != 0 )  && ( _heightIndex != landscape->getHeight() - 1 ) )
		&& landscape->getSurfaceItem( _widthIndex - 1, _heightIndex + 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _painter, _widthIndex - 1, _heightIndex + 1 );

} // LandscapeWidget::drawSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeWidget::drawWater(
		QPainter& _painter
	,	const unsigned int _widthIndex
	,	const unsigned int _heightIndex )
{
	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		landscape = m_landscapeEditorController.getEditableLandscape();

	QColor waterColor( 0, 120, 245 );
	QBrush surfaceItemBrash( waterColor );
	_painter.fillRect(
			QRect(
					_widthIndex * Resources::Landscape::CellSize
				,	_heightIndex * Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize )
		, surfaceItemBrash );

	QColor sandColor( 255, 200, 50 );
	QBrush sandBrash( sandColor );

	// top
	if ( ( _heightIndex == 0 ) || ( landscape->getSurfaceItem( _widthIndex, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.25 )
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize * 0.5
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// bottom
	if ( ( _heightIndex == landscape->getHeight() - 1 ) || ( landscape->getSurfaceItem( _widthIndex, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.25 )
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	Resources::Landscape::CellSize * 0.5
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// left
	if ( ( _widthIndex == 0 ) || ( landscape->getSurfaceItem( _widthIndex - 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.25 )
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.5 )
			,	sandBrash );

	// right
	if ( ( _widthIndex == landscape->getWidth() - 1 ) || ( landscape->getSurfaceItem( _widthIndex + 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.25 )
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.5 )
			,	sandBrash );

	// left top
	if (	( _widthIndex == 0  || _heightIndex == 0 )
		|| ( ( ( _widthIndex != 0 )  && ( _heightIndex != 0 ) )
		&& ( landscape->getSurfaceItem( _widthIndex - 1, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex - 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		))
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// right bottom
	if (	( ( _widthIndex == landscape->getWidth() - 1 )  || ( _heightIndex == landscape->getHeight() - 1 ) )
		|| ( ( ( _widthIndex != landscape->getWidth() - 1 )  && ( _heightIndex != landscape->getHeight() - 1 ) )
		&& ( landscape->getSurfaceItem( _widthIndex + 1, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex + 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		))
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// right top
	if (	( ( _widthIndex == landscape->getWidth() - 1 )  || ( _heightIndex == 0 ) )
		|| ( ( ( _widthIndex != landscape->getWidth() - 1 )  && ( _heightIndex != 0 ) )
		&& ( landscape->getSurfaceItem( _widthIndex + 1, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex + 1, _heightIndex) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// left bottom
	if (	( ( _widthIndex == 0 )  || ( _heightIndex == landscape->getHeight() - 1 ) )
		|| ( ( ( _widthIndex != 0 )  && ( _heightIndex != landscape->getHeight() - 1 ) )
		&& ( landscape->getSurfaceItem( _widthIndex - 1, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex - 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| landscape->getSurfaceItem( _widthIndex, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

} // LandscapeWidget::drawWater


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
