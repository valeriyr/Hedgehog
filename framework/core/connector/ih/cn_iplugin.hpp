
#ifndef __CN_IPLUGIN_HPP__
#define __CN_IPLUGIN_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPlugin
	:	public Tools::Core::IBase
{
	virtual void initialize( Tools::Core::IBase* _connector ) = 0;

	virtual void close() = 0;

	virtual Tools::Core::IBase* getInterface( const unsigned int _interfaceId ) = 0;
};

/*---------------------------------------------------------------------------*/

typedef Tools::Core::BaseWrapper< IPlugin > PluginWrapper;

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGIN_HPP__
