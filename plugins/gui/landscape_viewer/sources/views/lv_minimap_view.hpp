
#ifndef __LV_MINIMAP_VIEW_HPP__
#define __LV_MINIMAP_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
class MinimapWidget;

/*---------------------------------------------------------------------------*/

class MinimapView
	:	public QObject
	,	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MinimapView( const IEnvironment& _environment );

	virtual ~MinimapView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void showLandscape( const Core::LandscapeModel::ILandscape& _landscape );

	void clear();

/*---------------------------------------------------------------------------*/

	void setVisibilityRectSize( const float _relVisibleWidth, const float _relVisibleHeight );

	void setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight );

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onVisibilityRectChangedPosition( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::shared_ptr< MinimapWidget > m_minimapWidget;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_MINIMAP_VIEW_HPP__
