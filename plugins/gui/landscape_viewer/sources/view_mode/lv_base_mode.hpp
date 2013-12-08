
#ifndef __LV_BASE_MODE_HPP__
#define __LV_BASE_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/view_mode/lv_iview_mode.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class ViewsMediator;

/*---------------------------------------------------------------------------*/

class BaseMode
	:	public Tools::Core::BaseWrapper< IViewMode >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseMode( const IEnvironment& _environment );

	virtual ~BaseMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString getLandscapeFilePath() const;

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened( const QString& _filePath );

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::shared_ptr< ViewsMediator > m_viewsMediator;

	QString m_landscapeFilePath;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_BASE_MODE_HPP__
