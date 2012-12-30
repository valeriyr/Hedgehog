
#include "images_manager/sources/ph/im_ph.hpp"

#include "images_manager/sources/images_manager/im_images_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace ImagesManager {

/*---------------------------------------------------------------------------*/


ImagesManager::ImagesManager( const QString& _resourcesDirectory )
	:	m_resourcesDirectory( _resourcesDirectory )
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
	return QPixmap();

} // ImagesManager::getPixmap


/*---------------------------------------------------------------------------*/


const QIcon&
ImagesManager::getIcon( const QString& _resourcePath )
{
	return QIcon();

} // ImagesManager::getIcon


/*---------------------------------------------------------------------------*/

} // namespace ImagesManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
