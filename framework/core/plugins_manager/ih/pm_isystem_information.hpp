
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
	virtual const QString& getPluginsDirectory() const = 0;

	virtual const QString& getConfigDirectory() const = 0;

	virtual const QString& getResourcesDirectory() const = 0;

	virtual const QString& getApplicationName() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_ISYSTEM_INFORMATION_HPP__
