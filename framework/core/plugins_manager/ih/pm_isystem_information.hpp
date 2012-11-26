
#ifndef __CN_ISYSTEM_INFORMATION_HPP__
#define __CN_ISYSTEM_INFORMATION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct ISystemInformation
	:	public Tools::Core::IBase
{
	virtual const std::string& getPluginsDirectory() const = 0;

	virtual const std::string& getConfigDirectory() const = 0;

	virtual const std::string& getResourcesDirectory() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_ISYSTEM_INFORMATION_HPP__
