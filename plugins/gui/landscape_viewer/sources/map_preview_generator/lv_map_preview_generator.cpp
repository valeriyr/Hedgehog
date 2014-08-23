
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/map_preview_generator/lv_map_preview_generator.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/graphics_info/lv_isurface_item_graphics_info.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

const QSize IMapPreviewGenerator::ms_fixedWidgetSize = QSize( 300, 200 );

/*---------------------------------------------------------------------------*/


MapPreviewGenerator::MapPreviewGenerator( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // MapPreviewGenerator::MapPreviewGenerator


/*---------------------------------------------------------------------------*/


MapPreviewGenerator::~MapPreviewGenerator()
{
} // MapPreviewGenerator::~MapPreviewGenerator


/*---------------------------------------------------------------------------*/


void
MapPreviewGenerator::generate(
		QPixmap& _generateTo
	,	const GenerateLayers::Mask& _mask ) const
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	boost::intrusive_ptr< Core::LandscapeModel::ILandscape > landscape
		= locker->getLandscapeModel()->getLandscape();

	if ( _mask & GenerateLayers::Surface )
	{
		generateSurface( _generateTo, *landscape );
	}
	else
	{
		_generateTo = QPixmap( ms_fixedWidgetSize );
		_generateTo.fill( Qt::transparent );
	}

	if ( _mask & GenerateLayers::StartPoints )
		generateStartPoints( _generateTo, *landscape );

	if ( _mask & GenerateLayers::Objects )
		generateObjects( _generateTo, *locker->getLandscapeModel() );

} // MapPreviewGenerator::generate


/*---------------------------------------------------------------------------*/


void
MapPreviewGenerator::generateSurface(
		QPixmap& _generateTo
	,	const Plugins::Core::LandscapeModel::ILandscape& _landscape ) const
{
	QPixmap surface
		= QPixmap( QSize(
				_landscape.getWidth() * Resources::Landscape::CellSize
			,	_landscape.getHeight() * Resources::Landscape::CellSize ) );

	QPainter painter;
	painter.begin( &surface );
	painter.setRenderHint( QPainter::Antialiasing );

	for ( int i = 0; i < _landscape.getWidth(); ++i )
	{
		for ( int j = 0; j < _landscape.getHeight(); ++j )
		{
			boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
				surfaceItem = _landscape.getSurfaceItem( QPoint( i, j ) );

			boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
				surfaceItemGraphicsInfo = m_environment.getGraphicsInfo()->getSurfaceItemGraphicsInfo(
						m_environment.getString( Resources::Properties::SkinId )
					,	surfaceItem->getId() );

			painter.drawPixmap(
				QRect(
						i * Resources::Landscape::CellSize
					,	j * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize )
					,	m_environment.getPixmap(
								surfaceItemGraphicsInfo->getAtlasName()
							,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );
		}
	}

	_generateTo = surface.scaled( ms_fixedWidgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

} // MapPreviewGenerator::generateSurface


/*---------------------------------------------------------------------------*/


void
MapPreviewGenerator::generateStartPoints(
		QPixmap& _generateTo
	,	const Plugins::Core::LandscapeModel::ILandscape& _landscape ) const
{
	float scaleByX = static_cast< float >( ms_fixedWidgetSize.width() ) / ( _landscape.getWidth() * Resources::Landscape::CellSize );
	float scaleByY = static_cast< float >( ms_fixedWidgetSize.height() ) / ( _landscape.getHeight() * Resources::Landscape::CellSize );

	QPainter painter;
	painter.begin( &_generateTo );
	painter.setRenderHint( QPainter::Antialiasing );

	Plugins::Core::LandscapeModel::ILandscape::StartPointsIterator
		iterator = _landscape.getStartPointsIterator();

	while ( iterator->isValid() )
	{
		qreal posByX = ( iterator->current().m_point.x() * Resources::Landscape::CellSize ) * scaleByX;
		qreal posByY = ( iterator->current().m_point.y() * Resources::Landscape::CellSize ) * scaleByY;

		QPixmap pixmap( QSize( Resources::Landscape::CellSize * scaleByX, Resources::Landscape::CellSize * scaleByY ) );
		pixmap.fill( m_environment.getGraphicsInfo()->getStartPointColor( iterator->current().m_id ) );

		painter.drawPixmap(
				QRect( posByX, posByY, pixmap.width(), pixmap.height() )
			,	pixmap );

		iterator->next();
	}

} // MapPreviewGenerator::generateStartPoints


/*---------------------------------------------------------------------------*/


void
MapPreviewGenerator::generateObjects(
		QPixmap& _generateTo
	,	const Plugins::Core::LandscapeModel::ILandscapeModel& _landscapeModel ) const
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscape > landscape
		= _landscapeModel.getLandscape();

	float scaleByX = static_cast< float >( ms_fixedWidgetSize.width() ) / ( landscape->getWidth() * Resources::Landscape::CellSize );
	float scaleByY = static_cast< float >( ms_fixedWidgetSize.height() ) / ( landscape->getHeight() * Resources::Landscape::CellSize );

	QPainter painter;
	painter.begin( &_generateTo );
	painter.setRenderHint( QPainter::Antialiasing );

	Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection objectsCollection;
	landscape->fetchObjects( objectsCollection );

	Plugins::Core::LandscapeModel::ILandscape::ObjectsCollectionIterator
			begin = objectsCollection.begin()
		,	end = objectsCollection.end();

	for ( ; begin != end; ++begin )
	{
		boost::intrusive_ptr< Core::LandscapeModel::ILocateComponent > locateComponent
			= ( *begin )->getComponent< Core::LandscapeModel::ILocateComponent >( Plugins::Core::LandscapeModel::ComponentId::Locate );
		boost::intrusive_ptr< Core::LandscapeModel::IPlayer > player = _landscapeModel.getPlayer( **begin );

		for ( int x = locateComponent->getLocation().x(); x < locateComponent->getLocation().x() + locateComponent->getStaticData().m_size.width(); ++x )
		{
			for ( int y = locateComponent->getLocation().y(); y < locateComponent->getLocation().y() + locateComponent->getStaticData().m_size.height(); ++y )
			{
				qreal posByX = ( x * Resources::Landscape::CellSize ) * scaleByX;
				qreal posByY = ( y * Resources::Landscape::CellSize ) * scaleByY;

				QPixmap pixmap( QSize( Resources::Landscape::CellSize * scaleByX, Resources::Landscape::CellSize * scaleByY ) );
				pixmap.fill( player ? m_environment.getGraphicsInfo()->getStartPointColor( player->getStartPointId() ) : m_environment.getGraphicsInfo()->getNobodyObjectColor() );

				painter.drawPixmap(
						QRect( posByX, posByY, pixmap.width(), pixmap.height() )
					,	pixmap );
			}
		}
	}

} // MapPreviewGenerator::generateObjects


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/