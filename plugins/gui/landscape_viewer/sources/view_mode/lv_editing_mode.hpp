
#ifndef __LV_EDITING_MODE_HPP__
#define __LV_EDITING_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/view_mode/lv_iview_mode.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class DescriptionView;
class EditorView;
class MinimapView;
class ObjectsView;

/*---------------------------------------------------------------------------*/

class EditingMode
	:	public Tools::Core::BaseWrapper< IViewMode >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EditingMode( const IEnvironment& _environment );

	virtual ~EditingMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
		getCurrentLandscape() const;

	/*virtual*/ QString getLandscapeFilePath() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isPlayingMode() const;

	/*virtual*/ bool isEditingMode() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void openLandscape( const QString& _filePath );

	/*virtual*/ void closeLandscape();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape > m_editableLandscape;

	QString m_landscapeFilePath;

	boost::intrusive_ptr< DescriptionView > m_descriptionView;
	boost::intrusive_ptr< EditorView > m_editorView;
	boost::intrusive_ptr< MinimapView > m_minimapView;
	boost::intrusive_ptr< ObjectsView > m_objectsView;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_EDITING_MODE_HPP__
