
#include "images_manager/sources/ph/im_ph.hpp"

#include "images_manager/sources/images_manager/im_images_manager.hpp"

#include "images_manager/sources/internal_resources/im_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace ImagesManager {

/*---------------------------------------------------------------------------*/


ImagesManager::ImagesManager( const QString& _resourcesDirectory )
	:	m_resourcesDirectory( _resourcesDirectory )
	,	m_pixmapsCollection()
{
} // ImagesManager::ImagesManager


/*---------------------------------------------------------------------------*/


ImagesManager::~ImagesManager()
{
} // ImagesManager::~ImagesManager


/*---------------------------------------------------------------------------*/


const QPixmap&
ImagesManager::getPixmap( const QString& _resourcePath )
{
	PixmapsCollectionIteratorType iterator = m_pixmapsCollection.find( _resourcePath );

	if ( iterator != m_pixmapsCollection.end() )
		return *iterator->second;

	QString pixmapPath
		=	m_resourcesDirectory
		+	"/"
		+	Resources::ImagesDirecctory
		+	"/"
		+	_resourcePath
		+	Resources::ImageDefaultExtension;

	boost::shared_ptr< QPixmap > pixmap( new QPixmap() );
	bool resultOfLoading = pixmap->load( pixmapPath );
	assert( resultOfLoading );

	m_pixmapsCollection.insert( std::make_pair( _resourcePath, pixmap ) );

	return *pixmap;

} // ImagesManager::getPixmap


/*---------------------------------------------------------------------------*/


const QPixmap&
ImagesManager::getPixmap( const QString& _resourcePath, const QRect& _rect )
{
	QString path = generatePathForPixmapWithRect( _resourcePath, _rect );

	PixmapsCollectionIteratorType iterator = m_pixmapsCollection.find( path );
	if ( iterator != m_pixmapsCollection.end() )
		return *iterator->second;

	boost::shared_ptr< QPixmap > pixmap( new QPixmap( getPixmap( _resourcePath ).copy( _rect ) ) );

	m_pixmapsCollection.insert( std::make_pair( path, pixmap ) );

	return *pixmap;

} // ImagesManager::getPixmap


/*---------------------------------------------------------------------------*/


QString
ImagesManager::generatePathForPixmapWithRect( const QString& _resourcePath, const QRect& _rect )
{
	return
		QString( Resources::ImageWithRectPathFormat )
			.arg( _resourcePath )
			.arg( _rect.x() )
			.arg( _rect.y() )
			.arg( _rect.right() )
			.arg( _rect.bottom() );

} // ImagesManager::generatePathForPixmapWithRect


/*---------------------------------------------------------------------------*/

} // namespace ImagesManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
