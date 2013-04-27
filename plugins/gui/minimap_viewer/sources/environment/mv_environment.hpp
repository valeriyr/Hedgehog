
#ifndef __LE_ENVIRONMENT_HPP__
#define __LE_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "minimap_viewer/sources/environment/mv_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

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

	/*virtual*/ boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getSurfaceItem( const unsigned int _index ) const;

	/*virtual*/ boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getDefaultSurfaceItem() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QPixmap& getPixmap( const QString& _resourcePath, const QRect& _rect ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void changeVisibleAreaOnMainWindow(
			const float _relPosotionByX
		,	const float _relPosotionByY ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_ENVIRONMENT_HPP__
