
#ifndef __CN_PLUGINS_SERIALIZER_HPP__
#define __CN_PLUGINS_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/sources/plugins_serializer/cn_iplugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
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

	void onPluginElement(
			const unsigned int _pluginId
		,	const bool _loadAtStartup
		,	const std::string& _pluginName
		,	const std::string& _filePath
		);

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IPluginsManagerInternal& m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_SERIALIZER_HPP__
