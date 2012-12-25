
#ifndef __LE_ILANDSCAPE_EDITOR_CONTROLLER_HPP__
#define __LE_ILANDSCAPE_EDITOR_CONTROLLER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeEditorController
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void newLandscape() = 0;

	virtual void openLandscape() = 0;

	virtual void closeLandscape() = 0;

	virtual void saveLandscape() = 0;

	virtual void saveAsLandscape() = 0;

/*---------------------------------------------------------------------------*/

	virtual const QString& getLandscapeFilePath() const = 0;

	virtual Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		getEditableLandscape() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_ILANDSCAPE_EDITOR_CONTROLLER_HPP__
