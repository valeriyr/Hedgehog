
#ifndef __LV_OBJECT_INFO_VIEW_HPP__
#define __LV_OBJECT_INFO_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

#include "landscape_model/ih/lm_iobject.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class ObjectInfoView
	:	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ObjectInfoView( const IEnvironment& _environment );

	virtual ~ObjectInfoView();

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

	void onObjectMoved( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void setDescriptionForObject( const Core::LandscapeModel::IObject::IdType& _objectId );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	QString m_viewTitle;

	boost::shared_ptr< QTextEdit > m_mainWidget;

	Core::LandscapeModel::IObject::IdType m_showingObjectId;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_OBJECT_INFO_VIEW_HPP__
