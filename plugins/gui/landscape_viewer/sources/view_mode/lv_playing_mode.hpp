
#ifndef __LV_PLAYING_MODE_HPP__
#define __LV_PLAYING_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/view_mode/lv_iview_mode.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class PlayingMode
	:	public Tools::Core::BaseWrapper< IViewMode >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PlayingMode( const IEnvironment& _environment );

	virtual ~PlayingMode();

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

	QString m_landscapeFilePath;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_PLAYING_MODE_HPP__
