
#ifndef __LV_PLAYING_MODE_HPP__
#define __LV_PLAYING_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/view_mode/lv_base_mode.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class DescriptionView;
class LandscapeView;
class MinimapView;

/*---------------------------------------------------------------------------*/

class PlayingMode
	:	public BaseMode
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PlayingMode( const IEnvironment& _environment );

	virtual ~PlayingMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isPlayingMode() const;

	/*virtual*/ bool isEditingMode() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void openLandscape( const QString& _filePath );

	/*virtual*/ void closeLandscape();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< DescriptionView > m_descriptionView;
	boost::intrusive_ptr< LandscapeView > m_landscapeView;
	boost::intrusive_ptr< MinimapView > m_minimapView;

	QTimer m_timer;

/*---------------------------------------------------------------------------*/

	static const int ms_updatePeriod = 10;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_PLAYING_MODE_HPP__
