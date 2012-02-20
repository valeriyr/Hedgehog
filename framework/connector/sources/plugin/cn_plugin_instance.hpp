
/** Connector plugin instance declaration */

#ifndef __CN_PLUGIN_INSTANCE_HPP__
#define __CN_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugin.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

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

	/*virtual*/ void initialize( IBase* _connector );

	/*virtual*/ void close();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGIN_INSTANCE_HPP__
