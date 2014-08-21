
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

/*---------------------------------------------------------------------------*/

class CommandsExecutor
	:	public Tools::Core::BaseWrapper< ICommandsExecutor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CommandsExecutor( const IEnvironment& _environment );

	virtual ~CommandsExecutor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void newLandscape();

	/*virtual*/ void openLandscape();

	/*virtual*/ void closeLandscape();

	/*virtual*/ void saveLandscape();

	/*virtual*/ void saveAsLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void startGame();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void openLandscape( const QString& _fileName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_COMMANDS_EXECUTOR_HPP__
