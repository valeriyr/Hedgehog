
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

	virtual bool isPlayingMode() const = 0;

	virtual bool isEditingMode() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void ensureLandscapeEditingMode() = 0;

	virtual void ensurePlayingMode() = 0;

/*---------------------------------------------------------------------------*/

	virtual QString getLandscapeFilePath() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void openLandscape( const QString& _filePath ) = 0;

	virtual void closeLandscape() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ILANDSCAPE_VIEWER_HPP__
