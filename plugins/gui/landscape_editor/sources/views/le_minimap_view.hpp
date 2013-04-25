
#ifndef __LE_MINIMAP_VIEW_HPP__
#define __LE_MINIMAP_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ibase_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeEditorController;
struct ILandscapeRenderer;

class MinimapWidget;
class ViewsMediator;

/*---------------------------------------------------------------------------*/

class MinimapView
	:	public Tools::Core::BaseWrapper< IBaseView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MinimapView(
			const ILandscapeEditorController& _landscapeEditorController
		,	ILandscapeRenderer& _landscapeRenderer
		,	boost::shared_ptr< ViewsMediator > _viewsMediator );

	virtual ~MinimapView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void landscapeWasOpened();

	/*virtual*/ void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeEditorController& m_landscapeEditorController;

	boost::shared_ptr< MinimapWidget > m_minimapWidget;

	boost::shared_ptr< ViewsMediator > m_viewsMediator;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_MINIMAP_VIEW_HPP__
