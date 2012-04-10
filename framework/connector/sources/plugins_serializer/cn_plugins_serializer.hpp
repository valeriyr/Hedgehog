
/** Connector plugins serializer declaration part */

#ifndef __CN_PLUGINS_SERIALIZER_HPP__
#define __CN_PLUGINS_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/sources/plugins_serializer/cn_iplugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

class PluginsSerializer
	:	public BaseWrapper< IPluginsSerializer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginsSerializer();

	virtual ~PluginsSerializer();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_SERIALIZER_HPP__
