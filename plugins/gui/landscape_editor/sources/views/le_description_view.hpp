
#ifndef __LE_DESCRIPTION_VIEW_HPP__
#define __LE_DESCRIPTION_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ilandscape_editor_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class DescriptionView
	:	public Tools::Core::BaseWrapper< ILandscapeEditorView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	DescriptionView( const IEnvironment& _environment );

	virtual ~DescriptionView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget() const;

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

	const IEnvironment& m_environment;

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
