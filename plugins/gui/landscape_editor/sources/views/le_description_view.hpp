
#ifndef __LE_DESCRIPTION_VIEW_HPP__
#define __LE_DESCRIPTION_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ibase_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeEditorController;

/*---------------------------------------------------------------------------*/

class DescriptionView
	:	public Tools::Core::BaseWrapper< IBaseView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	DescriptionView( const ILandscapeEditorController& _landscapeEditorController );

	virtual ~DescriptionView();

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

	void setDefaultDescription();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeEditorController& m_landscapeEditorController;

	boost::shared_ptr< QTextEdit > m_descriptionView;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_DESCRIPTION_VIEW_HPP__
