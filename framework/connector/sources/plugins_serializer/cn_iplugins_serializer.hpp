
/** Connector plugins serializer interface */

#ifndef __CN_IPLUGINS_SERIALIZER_HPP__
#define __CN_IPLUGINS_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsSerializer
	:	public IBase
{
	virtual void loadPluginsData() = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGINS_SERIALIZER_HPP__
