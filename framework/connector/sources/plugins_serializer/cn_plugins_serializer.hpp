
/** Connector plugins serializer declaration part */

#ifndef __CN_PLUGINS_SERIALIZER_HPP__
#define __CN_PLUGINS_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/sources/plugins_serializer/cn_iplugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsManager;

/*---------------------------------------------------------------------------*/

class PluginsSerializer
	:	public BaseWrapper< IPluginsSerializer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginsSerializer( IPluginsManager& _pluginsManager );

	virtual ~PluginsSerializer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void loadPluginsData();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IPluginsManager& m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_SERIALIZER_HPP__
