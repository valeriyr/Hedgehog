
#ifndef __LV_ICOMMANDS_EXECUTOR_HPP__
#define __LV_ICOMMANDS_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct ICommandsExecutor
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void newLandscape() = 0;

	virtual void openLandscape() = 0;

	virtual void closeLandscape() = 0;

	virtual void saveLandscape() = 0;

	virtual void saveAsLandscape() = 0;

/*---------------------------------------------------------------------------*/

	virtual void startGame() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ICOMMANDS_EXECUTOR_HPP__
