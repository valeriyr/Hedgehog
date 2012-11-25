
#ifndef __CN_PLUGIN_INSTANCE_HPP__
#define __CN_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugin.hpp"
#include "connector/h/cn_interface_map.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsManager;
struct IPluginsManagerInternal;

/*---------------------------------------------------------------------------*/

class PluginInstance
	:	public PluginWrapper
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginInstance();

	virtual ~PluginInstance();

/*---------------------------------------------------------------------------*/

	INTERFACE_MAP_DECLARATION()

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initialize( IBase* _connector );

	/*virtual*/ void close();

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IPluginsManager > getPluginsManager() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IPluginsManagerInternal > m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGIN_INSTANCE_HPP__
