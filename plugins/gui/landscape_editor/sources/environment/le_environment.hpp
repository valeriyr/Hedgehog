
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

	/*virtual*/ boost::intrusive_ptr< ILandscapeEditorView > getObjectsView() const;

	/*virtual*/ boost::intrusive_ptr< ILandscapeEditorView > getEditorView() const;

	/*virtual*/ boost::intrusive_ptr< ILandscapeEditorView > getDescriptionView() const;

	/*virtual*/ boost::intrusive_ptr< ILandscapeEditorView > getMinimapView() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscapeEditorController >
		getLandscapeEditorController() const;

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
