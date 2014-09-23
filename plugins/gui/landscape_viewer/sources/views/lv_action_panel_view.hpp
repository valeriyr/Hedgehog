
#ifndef __LV_ACTION_PANEL_VIEW_HPP__
#define __LV_ACTION_PANEL_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class ViewsMediator;

/*---------------------------------------------------------------------------*/

class ActionPanelView
	:	public QObject
	,	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ActionPanelView( const IEnvironment& _environment, ViewsMediator& _viewsMediator );

	virtual ~ActionPanelView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onItemClicked( QListWidgetItem* _item );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectStateChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void updateView( const Tools::Core::Generators::IGenerator::IdType& _objectId );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	ViewsMediator& m_viewsMediator;

	Framework::Core::EventManager::Subscriber m_subscriber;

	QString m_viewTitle;

	boost::shared_ptr< QListWidget > m_mainWidget;

	Tools::Core::Generators::IGenerator::IdType m_showingObjectId;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ACTION_PANEL_VIEW_HPP__
