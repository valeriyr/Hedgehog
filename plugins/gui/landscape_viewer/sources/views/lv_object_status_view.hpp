
#ifndef __LV_OBJECT_STATUS_VIEW_HPP__
#define __LV_OBJECT_STATUS_VIEW_HPP__

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

/*---------------------------------------------------------------------------*/

class ObjectStatusView
	:	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ObjectStatusView( const IEnvironment& _environment );

	virtual ~ObjectStatusView();

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

	void onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event );

	void onTrainQueueChanged( const Framework::Core::EventManager::Event& _event );

	void onTrainProgressChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void updateBuildQueue();

	void updateProgressLabel( const int _progress );
	void updateProgressLabel();

	void clearBuildQueue();
	void clearProgressLabel();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	QString m_viewTitle;

	boost::shared_ptr< QWidget > m_mainWidget;

	QPushButton* m_currentObject;
	QListWidget* m_listWidget;
	QLabel* m_label;

	Tools::Core::Generators::IGenerator::IdType m_builderId;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_OBJECT_STATUS_VIEW_HPP__
