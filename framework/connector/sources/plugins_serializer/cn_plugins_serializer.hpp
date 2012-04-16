
#ifndef __CN_PLUGINS_SERIALIZER_HPP__
#define __CN_PLUGINS_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/sources/plugins_serializer/cn_iplugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsManagerInternal;

/*---------------------------------------------------------------------------*/

class PluginsSerializer
	:	public BaseWrapper< IPluginsSerializer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginsSerializer( IPluginsManagerInternal& _pluginsManager );

	virtual ~PluginsSerializer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void loadPluginsData();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IPluginsManagerInternal& m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_SERIALIZER_HPP__
