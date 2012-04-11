
/** Connector plugin manager declaration part */

#ifndef __CN_PLUGIN_DATA_HPP__
#define __CN_PLUGIN_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
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

	PluginData(
			const unsigned int _pluginId
		,	const bool _loadAtStartup
		,	const std::string& _pluginName
		,	const std::string& _filePath
		)
		:	m_pluginId( m_pluginId )
		,	m_loadAtStartup( _loadAtStartup )
		,	m_pluginName( _pluginName )
		,	m_filePath( _filePath )
		,	m_pluginStatus( State::NotLoaded )
		,	m_pluginPointer()
	{}

/*---------------------------------------------------------------------------*/

	const unsigned int m_pluginId;

	const bool m_loadAtStartup;

	const std::string m_pluginName;

	const std::string m_filePath;

	State::Enum m_pluginStatus;

	boost::intrusive_ptr< IPlugin > m_pluginPointer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGIN_DATA_HPP__
