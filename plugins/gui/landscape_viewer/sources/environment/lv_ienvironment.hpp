
#ifndef __LV_IENVIRONMENT_HPP__
#define __LV_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IGameInitializer;

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IGameInitializer > getGameInitializer() const = 0;

/*---------------------------------------------------------------------------*/

	virtual QString showOpenFileDialog() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void initializeLandscapeModel( const QString& _fileName ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void showCurrentLandscapeInView() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IENVIRONMENT_HPP__
