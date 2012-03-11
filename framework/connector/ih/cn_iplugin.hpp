
/** Common plugin interface */

#ifndef __CN_IPLUGIN_HPP__
#define __CN_IPLUGIN_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_ibase.hpp"

#include "connector/h/cn_base.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPlugin
	:	public IBase
{
	virtual void initialize( IBase* _connector ) = 0;

	virtual void close() = 0;

	virtual IBase* getInterface( const unsigned int _interfaceId ) = 0;
};

/*---------------------------------------------------------------------------*/

typedef BaseWrapper< IPlugin > PluginWrapper;

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGIN_HPP__
