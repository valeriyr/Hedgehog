
#ifndef __LE_ENVIRONMENT_HPP__
#define __LE_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/environment/le_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( const PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
		getDialogsManager() const;

	/*virtual*/ boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeEditor >
		getLandscapeEditor() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getSurfaceItem( const unsigned int _index ) const;

	/*virtual*/ boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getDefaultSurfaceItem() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QPixmap& getPixmap( const QString& _resourcePath, const QRect& _rect ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void showLandscapeOnMinimap(
		const Plugins::Core::LandscapeModel::ILandscape& _landscape ) const;

	/*virtual*/ void clearMinimap() const;

	/*virtual*/ void setMinimapVisibilityRectSize(
			const float _relVisibleWidth
		,	const float _relVisibleHeight ) const;

	/*virtual*/ void setMinimapVisibilityRectPosition(
			const float _relVisibleWidth
		,	const float _relVisibleHeight ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IBaseView > getObjectsView() const;

	/*virtual*/ boost::intrusive_ptr< IEditorView > getEditorView() const;

	/*virtual*/ boost::intrusive_ptr< IBaseView > getDescriptionView() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscapeEditorInternal > getGUILandscapeEditor() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_ENVIRONMENT_HPP__
