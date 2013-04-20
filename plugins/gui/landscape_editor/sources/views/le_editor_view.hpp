
#ifndef __LE_EDITOR_VIEW_HPP__
#define __LE_EDITOR_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ilandscape_editor_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeEditorController;
struct ILandscapeRenderer;

class LandscapeWidget;

/*---------------------------------------------------------------------------*/

class EditorView
	:	public Tools::Core::BaseWrapper< ILandscapeEditorView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EditorView(
			const ILandscapeEditorController& _landscapeEditorController
		,	ILandscapeRenderer& _landscapeRenderer );

	virtual ~EditorView();

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

	boost::shared_ptr< LandscapeWidget > m_landscapeWidget;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_EDITOR_VIEW_HPP__
