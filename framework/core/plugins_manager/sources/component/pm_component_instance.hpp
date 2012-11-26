
#ifndef __PM_COMPONENT_INSTANCE_HPP__
#define __PM_COMPONENT_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/sources/component/pm_icomponent_instance.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct IPluginsManagerInternal;
struct ISystemInformation;

/*---------------------------------------------------------------------------*/

class ComponentInstance
	:	public Tools::Core::BaseWrapper< IComponentInstance >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ComponentInstance();

	virtual ~ComponentInstance();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initialize( const SystemData& _systemData );

	/*virtual*/ void close();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< ISystemInformation > m_systemInformation;

	boost::intrusive_ptr< IPluginsManagerInternal > m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_COMPONENT_INSTANCE_HPP__
