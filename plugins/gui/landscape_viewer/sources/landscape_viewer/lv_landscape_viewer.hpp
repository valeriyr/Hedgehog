
#ifndef __LV_LANDSCAPE_VIEWER_HPP__
#define __LV_LANDSCAPE_VIEWER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class LandscapeViewer
	:	public Tools::Core::BaseWrapper< ILandscapeViewer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeViewer( const IEnvironment& _environment );

	virtual ~LandscapeViewer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IViewMode > getViewMode() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void ensureLandscapeEditingMode();

	/*virtual*/ void ensurePlayingMode();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::intrusive_ptr< IViewMode > m_viewMode;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ILANDSCAPE_VIEWER_HPP__
