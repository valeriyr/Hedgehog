
#ifndef __SE_IENVIRONMENT_HPP__
#define __SE_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools
{
	namespace Core
	{
		struct IMessenger;
	}
}

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Tools::Core::IMessenger > getSystemMessenger() const = 0;

	virtual const QString& getSystemConfigDirectory() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_IENVIRONMENT_HPP__
