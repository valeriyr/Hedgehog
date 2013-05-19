
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

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_EDITING_MODE_HPP__
