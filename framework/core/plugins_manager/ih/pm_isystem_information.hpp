
#ifndef __PM_ISYSTEM_INFORMATION_HPP__
#define __PM_ISYSTEM_INFORMATION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_SYSTEM_INFORMATION = 0;

/*---------------------------------------------------------------------------*/

struct ISystemInformation
	:	public Tools::Core::IBase
{
	virtual const std::string& getPluginsDirectory() const = 0;

	virtual const std::string& getConfigDirectory() const = 0;

	virtual const std::string& getResourcesDirectory() const = 0;

	virtual const std::string& getApplicationName() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_ISYSTEM_INFORMATION_HPP__
