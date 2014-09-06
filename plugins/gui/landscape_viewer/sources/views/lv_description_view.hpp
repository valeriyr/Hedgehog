
#ifndef __LV_DESCRIPTION_VIEW_HPP__
#define __LV_DESCRIPTION_VIEW_HPP__

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

class DescriptionView
	:	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	DescriptionView( const IEnvironment& _environment );

	virtual ~DescriptionView();

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

	void setDefaultDescription();

	void regenerateDescription();

/*---------------------------------------------------------------------------*/

	void onVictoryConditionChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	boost::shared_ptr< QTextEdit > m_descriptionView;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_DESCRIPTION_VIEW_HPP__
