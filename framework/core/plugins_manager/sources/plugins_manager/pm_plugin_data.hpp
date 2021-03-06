
#ifndef __PM_PLUGIN_DATA_HPP__
#define __PM_PLUGIN_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/ih/pm_iplugins_manager.hpp"
#include "plugins_manager/ih/pm_iplugin.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct PluginData
{

/*---------------------------------------------------------------------------*/

	struct State
	{
		enum Enum : qint32
		{
				NotLoaded = 0
			,	Loaded
			,	Loading
			,	Closed
		};
	};

/*---------------------------------------------------------------------------*/

	PluginData( const QString& _pluginName, const QString& _pluginFullPath )
		:	m_pluginName( _pluginName )
		,	m_pluginFullPath( _pluginFullPath )
		,	m_pluginState( State::NotLoaded )
		,	m_pluginPointer()
	{}

/*---------------------------------------------------------------------------*/

	const QString m_pluginName;

	const QString m_pluginFullPath;

	State::Enum m_pluginState;

	boost::intrusive_ptr< IPlugin > m_pluginPointer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_PLUGIN_DATA_HPP__
