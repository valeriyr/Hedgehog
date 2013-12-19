
#ifndef __LV_SELECTION_VIEW_HPP__
#define __LV_SELECTION_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class SelectionView
	:	public QObject
	,	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

	//Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SelectionView( const IEnvironment& _environment );

	virtual ~SelectionView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onUnitsSelectionChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	QString m_viewTitle;

	boost::shared_ptr< QListWidget > m_mainWidget;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_SELECTION_VIEW_HPP__
