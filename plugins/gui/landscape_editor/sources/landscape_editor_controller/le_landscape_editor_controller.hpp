
#ifndef __LE_LANDSCAPE_EDITOR_CONTROLLER_HPP__
#define __LE_LANDSCAPE_EDITOR_CONTROLLER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class LandscapeEditorController
	:	public Tools::Core::BaseWrapper< ILandscapeEditorController >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeEditorController( const IEnvironment& _environment );

	virtual ~LandscapeEditorController();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void newLandscape();

	/*virtual*/ void openLandscape();

	/*virtual*/ void closeLandscape();

	/*virtual*/ void saveLandscape();

	/*virtual*/ void saveAsLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getLandscapeFilePath() const;

	/*virtual*/ Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
		getEditableLandscape() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	QString m_landscapeFilePath;

	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr m_editableLandscape;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_EDITOR_CONTROLLER_HPP__
