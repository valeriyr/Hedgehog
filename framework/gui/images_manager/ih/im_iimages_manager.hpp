
#ifndef __IM_IIMAGES_MANAGER_HPP__
#define __IM_IIMAGES_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace ImagesManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_IMAGES_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IImagesManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap( const QString& _resourcePath ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ImagesManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __IM_IIMAGES_MANAGER_HPP__
