
#ifndef __LV_LANDSCAPE_VIEWER_HPP__
#define __LV_LANDSCAPE_VIEWER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IGraphicsInfoCache;

class DescriptionView;
class SettingsView;
class LandscapeView;
class MinimapView;
class ObjectsView;

class ViewsMediator;

/*---------------------------------------------------------------------------*/

class LandscapeViewer
	:	public Tools::Core::BaseWrapper< ILandscapeViewer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeViewer( const IEnvironment& _environment );

	virtual ~LandscapeViewer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString getLandscapeFilePath() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void openLandscape( const QString& _filePath );

	/*virtual*/ void closeLandscape();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::shared_ptr< ViewsMediator > m_viewsMediator;

	boost::intrusive_ptr< DescriptionView > m_descriptionView;
	boost::intrusive_ptr< SettingsView > m_settingsView;
	boost::intrusive_ptr< LandscapeView > m_LandscapeView;
	boost::intrusive_ptr< MinimapView > m_minimapView;
	boost::intrusive_ptr< ObjectsView > m_objectsView;

	QString m_landscapeFilePath;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ILANDSCAPE_VIEWER_HPP__
