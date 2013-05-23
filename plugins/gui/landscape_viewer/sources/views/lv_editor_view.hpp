
#ifndef __LV_EDITOR_VIEW_HPP__
#define __LV_EDITOR_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

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

struct IEnvironment;

class LandscapeEditorScene;
class LandscapeWidget;

class ViewsMediator;

/*---------------------------------------------------------------------------*/

class EditorView
	:	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EditorView( const IEnvironment& _environment, const ViewsMediator& _viewsMediator );

	virtual ~EditorView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened(
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape > _landscape );

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const ViewsMediator& m_viewsMediator;

	boost::shared_ptr< LandscapeEditorScene > m_landscapeScene;

	boost::shared_ptr< LandscapeWidget > m_landscapeWidget;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_EDITOR_VIEW_HPP__
