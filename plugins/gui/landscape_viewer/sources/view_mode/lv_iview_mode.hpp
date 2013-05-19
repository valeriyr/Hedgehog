
#ifndef __LV_IVIEW_MODE_HPP__
#define __LV_IVIEW_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct IEditableLandscape;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IViewMode
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
		getCurrentLandscape() const = 0;

	virtual QString getLandscapeFilePath() const = 0;

/*---------------------------------------------------------------------------*/

	virtual bool isPlayingMode() const = 0;

	virtual bool isEditingMode() const = 0;

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

#endif // __LV_IVIEW_MODE_HPP__
