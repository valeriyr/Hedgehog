
#ifndef __LV_ILANDSCAPE_VIEWER_HPP__
#define __LV_ILANDSCAPE_VIEWER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IViewMode;

/*---------------------------------------------------------------------------*/

struct ILandscapeViewer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual QString getLandscapeFilePath() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void initLandscape( const QString& _filePath ) = 0;

	virtual void startSimulation( const Plugins::Core::LandscapeModel::ILandscapeModel::PlayersSturtupDataCollection& _collection ) = 0;

	virtual void closeLandscape() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ILANDSCAPE_VIEWER_HPP__
