
#ifndef __LE_EDITOR_VIEW_HPP__
#define __LE_EDITOR_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ibase_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace GUI
	{
		namespace ImagesManager
		{
			struct IImagesManager;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeEditorController;
class LandscapeScene;

/*---------------------------------------------------------------------------*/

class EditorView
	:	public Tools::Core::BaseWrapper< IBaseView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EditorView(
			const ILandscapeEditorController& _landscapeEditorController
		,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager );

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

	boost::shared_ptr< LandscapeScene > m_landscapeScene;

	boost::shared_ptr< QGraphicsView > m_landscapeWidget;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_EDITOR_VIEW_HPP__
