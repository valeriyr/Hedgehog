
#ifndef __LV_ILANDSCAPE_VIEWER_HPP__
#define __LV_ILANDSCAPE_VIEWER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IViewMode;

/*---------------------------------------------------------------------------*/

struct ILandscapeViewer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IViewMode > getViewMode() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void ensureLandscapeEditingMode() = 0;

	virtual void ensurePlayingMode() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ILANDSCAPE_VIEWER_HPP__
