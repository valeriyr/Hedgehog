
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

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem >
		getSelectedSurfaceItem() const;

	/*virtual*/ void setSelectedSurfaceItem(
		boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem > _item );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getLandscapeFilePath() const;

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
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

	boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape > m_editableLandscape;

	boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem > m_selectedSurfaceItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_EDITOR_CONTROLLER_HPP__
