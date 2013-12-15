
#ifndef __LV_COMMANDS_EXECUTOR_HPP__
#define __LV_COMMANDS_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/commands_executor/lv_icommands_executor.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscapeViewer;

/*---------------------------------------------------------------------------*/

class CommandsExecutor
	:	public Tools::Core::BaseWrapper< ICommandsExecutor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CommandsExecutor( const IEnvironment& _environment, ILandscapeViewer& _landscapeViewer );

	virtual ~CommandsExecutor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void newLandscape();

	/*virtual*/ void openLandscape();

	/*virtual*/ void closeLandscape();

	/*virtual*/ void saveLandscape();

	/*virtual*/ void saveAsLandscape();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	ILandscapeViewer& m_landscapeViewer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_COMMANDS_EXECUTOR_HPP__
