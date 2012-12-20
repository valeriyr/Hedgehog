
#ifndef __CON_IENVIRONMENT_HPP__
#define __CON_IENVIRONMENT_HPP__

#include "intrusive_base/ib_ibase.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace Core
	{
		namespace CommandsManager
		{
			struct ICommandsRegistry;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		getCommandsRegistry() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_IENVIRONMENT_HPP__
