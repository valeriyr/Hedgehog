
#ifndef __CN_PLUGIN_DATA_HPP__
#define __CN_PLUGIN_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugins_manager.hpp"
#include "connector/ih/cn_iplugin.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct PluginData
{

/*---------------------------------------------------------------------------*/

	struct State
	{
		enum Enum
		{
				NotLoaded = 0
			,	Loaded
			,	Loading
		};
	};

/*---------------------------------------------------------------------------*/

	PluginData( const std::string& _pluginName )
		:	m_pluginName( _pluginName )
		,	m_pluginState( State::NotLoaded )
		,	m_pluginPointer()
	{}

/*---------------------------------------------------------------------------*/

	const std::string m_pluginName;

	State::Enum m_pluginState;

	boost::intrusive_ptr< IPlugin > m_pluginPointer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGIN_DATA_HPP__
