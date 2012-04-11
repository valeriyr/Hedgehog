
/** Connector plugin manager implementation part */

#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugins_manager/cn_plugins_manager.hpp"

#include "connector/h/cn_plugin_factory.hpp"

#include "connector/sources/plugins_manager/cn_plugin_data.hpp"
#include "connector/sources/resources/cn_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


PluginsManager::PluginsManager()
	:	m_pluginsCollection()
{
} // PluginsManager::PluginsManager


/*---------------------------------------------------------------------------*/


PluginsManager::~PluginsManager()
{
} // PluginsManager::~PluginsManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBase >
PluginsManager::getPluginInterface( const unsigned int _pluginId, const unsigned int _interfaceId )
{
	PluginsCollectionTypeIterator iterator( m_pluginsCollection.find( _pluginId ) );

	if ( iterator == m_pluginsCollection.end() )
		return boost::intrusive_ptr< IBase >();

	if ( iterator->second->m_pluginState == PluginData::State::Loading )	// We can't get interface from plugin
		throw std::exception();												// witch is loading!

	loadPluginIfNeeded( *iterator->second );

	return iterator->second->m_pluginPointer->getInterface( _interfaceId );

} // PluginsManager::getPluginInterface


/*---------------------------------------------------------------------------*/


bool
PluginsManager::isPluginLoaded( const unsigned int _pluginId ) const
{
	PluginsCollectionTypeIterator iterator( m_pluginsCollection.find( _pluginId ) );

	return
			( iterator != m_pluginsCollection.end() )
		&&	iterator->second->m_pluginState == PluginData::State::Loaded;

} // PluginsManager::isPluginLoaded


/*---------------------------------------------------------------------------*/


void
PluginsManager::registerPlugin( boost::shared_ptr< PluginData > _pluginData )
{
	assert( _pluginData );
	assert( m_pluginsCollection.find( _pluginData->m_pluginId ) == m_pluginsCollection.end() );

	m_pluginsCollection.insert( std::make_pair( _pluginData->m_pluginId, _pluginData ) );

} // PluginsManager::registerPlugin


/*---------------------------------------------------------------------------*/


void
PluginsManager::loadStartupPlugins()
{
	PluginsCollectionTypeIterator
			begin = m_pluginsCollection.begin()
		,	end = m_pluginsCollection.end();

	for( ; begin != end; ++begin )
	{
		if ( begin->second->m_loadAtStartup )
			loadPluginIfNeeded( *begin->second );
	}

} // PluginsManager::loadStartupPlugins


/*---------------------------------------------------------------------------*/


void
PluginsManager::closeAllPlugins()
{
	PluginsCollectionTypeIterator
			begin = m_pluginsCollection.begin()
		,	end = m_pluginsCollection.end();

	for( ; begin != end; ++begin )
	{
		if ( begin->second->m_pluginState == PluginData::State::Loaded )
		{
			assert( begin->second->m_pluginState != PluginData::State::Loading );

			begin->second->m_pluginPointer->close();
			begin->second->m_pluginPointer.reset();

			begin->second->m_pluginState = PluginData::State::NotLoaded;
		}
	}

} // PluginsManager::closeAllPlugins


/*---------------------------------------------------------------------------*/


void
PluginsManager::loadPluginIfNeeded( PluginData& _pluginData )
{
	assert( _pluginData.m_pluginState != PluginData::State::Loading );

	if ( _pluginData.m_pluginState == PluginData::State::Loaded )
		return;

	_pluginData.m_pluginState = PluginData::State::Loading;

	PluginFactoryPtr connectorFactory
		= ( PluginFactoryPtr ) QLibrary::resolve(
				_pluginData.m_filePath.c_str()
			,	PluginFactoryName
			);
	assert( connectorFactory );

	_pluginData.m_pluginPointer.reset( connectorFactory() );
	assert( _pluginData.m_pluginPointer );

	_pluginData.m_pluginPointer->initialize( this );

	_pluginData.m_pluginState = PluginData::State::Loaded;

} // PluginsManager::loadPluginIfNeeded


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
