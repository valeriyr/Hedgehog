
#ifndef __LV_LANDSCAPE_VIEW_HPP__
#define __LV_LANDSCAPE_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class LandscapeScene;
class LandscapeWidget;
class ViewsMediator;

/*---------------------------------------------------------------------------*/

class LandscapeView
	:	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeView( const IEnvironment& _environment, const ViewsMediator& _viewsMediator );

	virtual ~LandscapeView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened(
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscape > _landscape );

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const ViewsMediator& m_viewsMediator;

	QString m_viewTitle;

	boost::shared_ptr< LandscapeScene > m_landscapeScene;

	boost::shared_ptr< LandscapeWidget > m_landscapeWidget;

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

#endif // __LV_LANDSCAPE_VIEW_HPP__
