
#ifndef __LM_ISURFACE_ITEM_HPP__
#define __LM_ISURFACE_ITEM_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItem
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual unsigned int getIndex() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QString& getBundlePath() const = 0;

	virtual const QRect& getRectInBundle() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISURFACE_ITEM_HPP__
