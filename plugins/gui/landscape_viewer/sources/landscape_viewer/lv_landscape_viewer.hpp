
#ifndef __LV_LANDSCAPE_VIEWER_HPP__
#define __LV_LANDSCAPE_VIEWER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class LandscapeViewer
	:	public Tools::Core::BaseWrapper< ILandscapeViewer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeViewer();

	virtual ~LandscapeViewer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void startUpdateViewTimer();

	/*virtual*/ void stopUpdateViewTimer();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ILANDSCAPE_VIEWER_HPP__
