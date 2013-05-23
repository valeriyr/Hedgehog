
#ifndef __LV_OBJECTS_VIEW_HPP__
#define __LV_OBJECTS_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ISurfaceItem;
		}
	}
}

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

	void currentSurfaceItemWasChanged(
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > _surfaceItem );

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onCurrentItemChanged( QTreeWidgetItem* _current, QTreeWidgetItem* _previous );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const ViewsMediator& m_viewsMediator;

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
