
#ifndef __CN_IPLUGINS_SERIALIZER_HPP__
#define __CN_IPLUGINS_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsSerializer
	:	public Tools::Core::IBase
{
	virtual void loadPluginsList() = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGINS_SERIALIZER_HPP__
