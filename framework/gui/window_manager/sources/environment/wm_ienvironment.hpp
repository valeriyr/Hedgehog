
#ifndef __WM_IENVIRONMENT_HPP__
#define __WM_IENVIRONMENT_HPP__

#include "intrusive_base/ib_ibase.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace Core
	{
		namespace CommandsManager
		{
			struct ICommandExecutor;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandExecutor >
		getCommandExecutor() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_IENVIRONMENT_HPP__
