
#ifndef __LE_MINIMAP_VIEW_HPP__
#define __LE_MINIMAP_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "minimap_viewer/ih/mv_iminimap_viewer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
class MinimapWidget;

/*---------------------------------------------------------------------------*/

class MinimapView
	:	public QObject
	,	public Tools::Core::BaseWrapper< IMinimapViewer >
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

	/*virtual*/ void showLandscape( const Core::LandscapeModel::ILandscape& _landscape );

	/*virtual*/ void clear();

	/*virtual*/ void setVisibilityRectSize( const float _relVisibleWidth, const float _relVisibleHeight );

	/*virtual*/ void setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight );

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

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_MINIMAP_VIEW_HPP__
