
#ifndef __LV_EDITING_MODE_HPP__
#define __LV_EDITING_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/view_mode/lv_base_mode.hpp"

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

class DescriptionView;
class SettingsView;
class EditorView;
class MinimapView;
class ObjectsView;

/*---------------------------------------------------------------------------*/

class EditingMode
	:	public BaseMode
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EditingMode( const IEnvironment& _environment );

	virtual ~EditingMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isPlayingMode() const;

	/*virtual*/ bool isEditingMode() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void openLandscape( const QString& _filePath );

	/*virtual*/ void closeLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
		getEditingLandscape() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape > m_landscape;

	boost::intrusive_ptr< DescriptionView > m_descriptionView;
	boost::intrusive_ptr< SettingsView > m_settingsView;
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
