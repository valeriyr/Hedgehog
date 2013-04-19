
#ifndef __LE_MINIMAP_VIEW_HPP__
#define __LE_MINIMAP_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ilandscape_editor_view.hpp"

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
class MinimapWidget;

/*---------------------------------------------------------------------------*/

class MinimapView
	:	public Tools::Core::BaseWrapper< ILandscapeEditorView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MinimapView(
			const ILandscapeEditorController& _landscapeEditorController
		,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager );

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

	Framework::GUI::ImagesManager::IImagesManager& m_imagesManager;

	boost::shared_ptr< MinimapWidget > m_minimapWidget;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_MINIMAP_VIEW_HPP__
