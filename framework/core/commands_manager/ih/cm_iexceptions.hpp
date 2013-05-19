
#ifndef __CM_IEXCEPTIONS_HPP__
#define __CM_IEXCEPTIONS_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

struct IException
	:	public Tools::Core::IBase
{
	virtual QString what() const = 0;
};

/*---------------------------------------------------------------------------*/

struct IUnknownCommandException
	:	public IException
{
};

/*---------------------------------------------------------------------------*/

struct IDisabledCommandException
	:	public IException
{
};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_IEXCEPTIONS_HPP__
