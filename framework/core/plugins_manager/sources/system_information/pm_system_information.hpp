
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

	/*virtual*/ const QString& getPluginsDirectory() const;

	/*virtual*/ const QString& getConfigDirectory() const;

	/*virtual*/ const QString& getResourcesDirectory() const;

	/*virtual*/ const QString& getApplicationName() const;

	/*virtual*/ const QString& getSystemMessengerPluginName() const;

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
