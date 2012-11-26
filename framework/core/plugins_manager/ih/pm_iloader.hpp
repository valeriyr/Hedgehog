
#ifndef __PM_ILOADER_HPP__
#define __PM_ILOADER_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/h/pm_export.hpp"
#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


struct ILoader
	:	public Tools::Core::IBase
{
	virtual void load( const std::string& _pluginsDirectory ) = 0;

	virtual void unload() = 0;
};


/*---------------------------------------------------------------------------*/

PLUGINS_MANAGER_EXPORT
		boost::intrusive_ptr< ILoader >
		createLoader();

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_ILOADER_HPP__
