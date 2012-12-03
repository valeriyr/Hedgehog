
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

struct SystemData;

/*---------------------------------------------------------------------------*/


struct ILoader
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::intrusive_ptr< ILoader >
		Ptr;

/*---------------------------------------------------------------------------*/

	virtual void load( const SystemData& _systemData ) = 0;

	virtual void unload() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

PLUGINS_MANAGER_EXPORT ILoader::Ptr createLoader();

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_ILOADER_HPP__
