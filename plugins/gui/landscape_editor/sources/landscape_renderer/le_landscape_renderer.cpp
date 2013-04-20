
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_renderer/le_landscape_renderer.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeRenderer::LandscapeRenderer( Framework::GUI::ImagesManager::IImagesManager& _imagesManager )
	:	m_imagesManager( _imagesManager )
{
} // LandscapeRenderer::LandscapeRenderer


/*---------------------------------------------------------------------------*/


LandscapeRenderer::~LandscapeRenderer()
{
} // LandscapeRenderer::~LandscapeRenderer


/*---------------------------------------------------------------------------*/


void
LandscapeRenderer::renderSurface(
		const Core::LandscapeModel::IEditableLandscape& _landscape
	,	QPixmap& _pixmap )
{
	_pixmap
		= QPixmap( QSize(
				_landscape.getWidth() * Resources::Landscape::CellSize
			,	_landscape.getHeight() * Resources::Landscape::CellSize ) );

	QPainter painter;
	painter.begin( &_pixmap );
	painter.setRenderHint( QPainter::Antialiasing );

	for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
		for ( unsigned int j = 0; j < _landscape.getHeight(); ++j )
			drawSurfaceItem( _landscape, painter, i, j );

	/*for ( unsigned int i = 0; i < _landscape.getWidth(); ++i )
		painter.drawLine(
				i * Resources::Landscape::CellSize
			,	0
			,	i * Resources::Landscape::CellSize
			,	_paintDevice.size().height() );

	for ( unsigned int i = 0; i < _landscape.getHeight(); ++i )
		painter.drawLine(
				0
			,	i * Resources::Landscape::CellSize
			,	_paintDevice.size().width()
			,	i * Resources::Landscape::CellSize );*/

} // LandscapeRenderer::renderSurface


/*---------------------------------------------------------------------------*/


void
LandscapeRenderer::renderObjects(
		const Core::LandscapeModel::IEditableLandscape& _landscape
	,	QPixmap& _pixmap )
{
	_pixmap
		= QPixmap( QSize(
				_landscape.getWidth() * Resources::Landscape::CellSize
			,	_landscape.getHeight() * Resources::Landscape::CellSize ) );

	_pixmap.fill( Qt::transparent );

	QPainter painter;
	painter.begin( &_pixmap );
	painter.setRenderHint( QPainter::Antialiasing );

	QBrush surfaceItemBrash( QColor( 111, 111, 111 ) );
	painter.fillRect(
			QRect(
					3 * Resources::Landscape::CellSize
				,	3 * Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize
				,	Resources::Landscape::CellSize )
		, surfaceItemBrash );

} // LandscapeRenderer::renderObjects


/*---------------------------------------------------------------------------*/


void
LandscapeRenderer::drawSurfaceItem(
		const Core::LandscapeModel::IEditableLandscape& _landscape
	,	QPainter& _painter
	,	const unsigned int _widthIndex
	,	const unsigned int _heightIndex )
{
	Plugins::Core::LandscapeModel::SurfaceItems::Enum
		surfaceItem = _landscape.getSurfaceItem( _widthIndex, _heightIndex );

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
		drawWater( _landscape, _painter, _widthIndex, _heightIndex );
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
	if ( ( _heightIndex != 0 ) && ( _landscape.getSurfaceItem( _widthIndex, _heightIndex - 1 )  == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _landscape, _painter, _widthIndex, _heightIndex - 1 );

	// bottom
	if ( ( _heightIndex != _landscape.getHeight() - 1 ) && ( _landscape.getSurfaceItem( _widthIndex, _heightIndex + 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _landscape, _painter, _widthIndex, _heightIndex + 1 );

	// left
	if ( ( _widthIndex != 0 ) && ( _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex ) == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _landscape, _painter, _widthIndex - 1, _heightIndex );

	// right
	if ( ( _widthIndex != _landscape.getWidth() - 1 ) && ( _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex ) == Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		drawWater( _landscape, _painter, _widthIndex + 1, _heightIndex );

	// left top
	if (	( _widthIndex != 0  && _heightIndex != 0 )
		&& _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex - 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _landscape, _painter, _widthIndex - 1, _heightIndex - 1 );

	// right bottom
	if (	( ( _widthIndex != _landscape.getWidth() - 1 )  && ( _heightIndex != _landscape.getHeight() - 1 ) )
		&& _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex + 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _landscape, _painter, _widthIndex + 1, _heightIndex + 1 );

	// right top
	if (	( ( _widthIndex != _landscape.getWidth() - 1 )  && ( _heightIndex != 0 ) )
		&& _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex - 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _landscape, _painter, _widthIndex + 1, _heightIndex - 1 );

	// left bottom
	if (	( ( _widthIndex != 0 )  && ( _heightIndex != _landscape.getHeight() - 1 ) )
		&& _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex + 1 ) == Plugins::Core::LandscapeModel::SurfaceItems::Water
		)
		drawWater( _landscape, _painter, _widthIndex - 1, _heightIndex + 1 );

} // LandscapeRenderer::drawSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeRenderer::drawWater(
		const Core::LandscapeModel::IEditableLandscape& _landscape
	,	QPainter& _painter
	,	const unsigned int _widthIndex
	,	const unsigned int _heightIndex )
{
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
	if ( ( _heightIndex == 0 ) || ( _landscape.getSurfaceItem( _widthIndex, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.25 )
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize * 0.5
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// bottom
	if ( ( _heightIndex == _landscape.getHeight() - 1 ) || ( _landscape.getSurfaceItem( _widthIndex, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.25 )
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	Resources::Landscape::CellSize * 0.5
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// left
	if ( ( _widthIndex == 0 ) || ( _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.25 )
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.5 )
			,	sandBrash );

	// right
	if ( ( _widthIndex == _landscape.getWidth() - 1 ) || ( _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water ) )
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
		&& ( _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		))
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// right bottom
	if (	( ( _widthIndex == _landscape.getWidth() - 1 )  || ( _heightIndex == _landscape.getHeight() - 1 ) )
		|| ( ( ( _widthIndex != _landscape.getWidth() - 1 )  && ( _heightIndex != _landscape.getHeight() - 1 ) )
		&& ( _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		))
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// right top
	if (	( ( _widthIndex == _landscape.getWidth() - 1 )  || ( _heightIndex == 0 ) )
		|| ( ( ( _widthIndex != _landscape.getWidth() - 1 )  && ( _heightIndex != 0 ) )
		&& ( _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex + 1, _heightIndex) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex, _heightIndex - 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	_heightIndex * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

	// left bottom
	if (	( ( _widthIndex == 0 )  || ( _heightIndex == _landscape.getHeight() - 1 ) )
		|| ( ( ( _widthIndex != 0 )  && ( _heightIndex != _landscape.getHeight() - 1 ) )
		&& ( _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex - 1, _heightIndex ) != Plugins::Core::LandscapeModel::SurfaceItems::Water
		|| _landscape.getSurfaceItem( _widthIndex, _heightIndex + 1 ) != Plugins::Core::LandscapeModel::SurfaceItems::Water )
		) )
		_painter.fillRect(
				QRect(
						_widthIndex * Resources::Landscape::CellSize
					,	_heightIndex * Resources::Landscape::CellSize + ( Resources::Landscape::CellSize * 0.75 )
					,	Resources::Landscape::CellSize * 0.25
					,	Resources::Landscape::CellSize * 0.25 )
			,	sandBrash );

} // LandscapeRenderer::drawWater


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
