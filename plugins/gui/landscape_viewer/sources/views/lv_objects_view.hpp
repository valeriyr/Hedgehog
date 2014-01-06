
#ifndef __LV_OBJECTS_VIEW_HPP__
#define __LV_OBJECTS_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class ViewsMediator;

/*---------------------------------------------------------------------------*/

class ObjectsView
	:	public QObject
	,	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ObjectsView(
			const IEnvironment& _environment
		,	const ViewsMediator& _viewsMediator
		,	QObject* _parent = NULL );

	virtual ~ObjectsView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::Id& _id );

	void currentObjectWasChanged( const QString& _name );

	void controlItemSelected();

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onCurrentItemChanged( QTreeWidgetItem* _current, QTreeWidgetItem* _previous );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onSettingChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void fillWithSurfaceItems( const QString& _skinId, QTreeWidgetItem* _parentNode );

	void fillWithObjectItems( const QString& _skinId, QTreeWidgetItem* _parentNode );

	void fill();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const ViewsMediator& m_viewsMediator;

	Framework::Core::EventManager::Subscriber m_subscriber;

	boost::shared_ptr< QTreeWidget > m_objectsView;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_OBJECTS_VIEW_HPP__
