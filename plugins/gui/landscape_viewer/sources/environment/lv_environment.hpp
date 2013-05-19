
#ifndef __LV_ENVIRONMENT_HPP__
#define __LV_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString showOpenFileDialog() const;

	/*virtual*/ QString showSaveFileDialog() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QPixmap& getPixmap( const QString& _resourcePath, const QRect& _rect ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initializeLandscape( const QString& _fileName ) const;

	/*virtual*/ void closeLandscape() const;

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
		getLandscape() const;

	/*virtual*/ void saveLandscape(
			const QString& _fileName
		,	const Core::LandscapeModel::ILandscape& _landscape ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void runGameManager() const;

	/*virtual*/ void stopGameManager() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void selectItemsInModel(
			const Core::LandscapeModel::Point& _from
		,	const Core::LandscapeModel::Point& _to ) const;

	/*virtual*/ void moveSelectedItems( const Core::LandscapeModel::Point& _to ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ENVIRONMENT_HPP__
