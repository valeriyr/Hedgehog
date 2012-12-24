
#ifndef __LE_BASE_COMMAND_HPP__
#define __LE_BASE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommand.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class BaseCommand
	:	public Tools::Core::BaseWrapper< Framework::Core::CommandsManager::ICommand >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseCommand( const IEnvironment& _environment );

	virtual ~BaseCommand();

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_BASE_COMMAND_HPP__