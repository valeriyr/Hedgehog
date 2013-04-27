
#ifndef __LE_EDITOR_VIEW_HPP__
#define __LE_EDITOR_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ieditor_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class LandscapeScene;
class LandscapeView;

/*---------------------------------------------------------------------------*/

class EditorView
	:	public QObject
	,	public Tools::Core::BaseWrapper< IEditorView >
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EditorView( const IEnvironment& _environment );

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

	/*virtual*/ void setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight );

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onLandscapeViewWasResized( const float _visibleWidth, const float _visibleHeight );

	void onVisibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

	void onLandscapeWasChanged();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::shared_ptr< LandscapeScene > m_landscapeScene;

	boost::shared_ptr< LandscapeView > m_landscapeWidget;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_EDITOR_VIEW_HPP__
