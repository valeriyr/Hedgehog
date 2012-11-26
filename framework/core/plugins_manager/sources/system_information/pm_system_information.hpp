
#ifndef __PM_SYSTEM_INFORMATION_HPP__
#define __PM_SYSTEM_INFORMATION_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/ih/pm_isystem_information.hpp"
#include "plugins_manager/h/pm_system_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

class SystemInformation
	:	public Tools::Core::BaseWrapper< ISystemInformation >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SystemInformation( const SystemData& _systemData );

	virtual ~SystemInformation();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const std::string& getPluginsDirectory() const;

	/*virtual*/ const std::string& getConfigDirectory() const;

	/*virtual*/ const std::string& getResourcesDirectory() const;

	/*virtual*/ const std::string& getApplicationName() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const SystemData m_systemData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_SYSTEM_INFORMATION_HPP__
