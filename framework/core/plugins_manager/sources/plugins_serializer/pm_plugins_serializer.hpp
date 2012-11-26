
#ifndef __PM_PLUGINS_SERIALIZER_HPP__
#define __PM_PLUGINS_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct IPluginsManagerInternal;
struct ISystemInformation;

/*---------------------------------------------------------------------------*/

class PluginsSerializer
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginsSerializer(
			IPluginsManagerInternal& _pluginsManager
		,	const ISystemInformation& _systemInformation );

	~PluginsSerializer();

/*---------------------------------------------------------------------------*/

	void loadPluginsList();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IPluginsManagerInternal& m_pluginsManager;

	const ISystemInformation& m_systemInformation;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_PLUGINS_SERIALIZER_HPP__
