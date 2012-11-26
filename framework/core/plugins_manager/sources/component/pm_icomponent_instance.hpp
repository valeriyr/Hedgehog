
#ifndef __PM_ICOMPONENT_INSTANCE_HPP__
#define __PM_ICOMPONENT_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct SystemData;

/*---------------------------------------------------------------------------*/

struct IComponentInstance
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void initialize( const SystemData& _systemData ) = 0;

	virtual void close() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_ICOMPONENT_INSTANCE_HPP__
