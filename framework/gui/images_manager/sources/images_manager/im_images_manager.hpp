
#ifndef __IM_IMAGES_MANAGER_HPP__
#define __IM_IMAGES_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "images_manager/ih/im_iimages_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace ImagesManager {

/*---------------------------------------------------------------------------*/

class ImagesManager
	:	public Tools::Core::BaseWrapper< IImagesManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ImagesManager( const QString& _resourcesDirectory );

	virtual ~ImagesManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QPixmap& getPixmap( const QString& _resourcePath );

	/*virtual*/ const QIcon& getIcon( const QString& _resourcePath );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QString m_resourcesDirectory;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ImagesManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __IM_IIMAGES_MANAGER_HPP__
