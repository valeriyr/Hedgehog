
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
	PluginsCollectionTypeIterator
			begin = m_pluginsCollection.begin()
		,	end = m_pluginsCollection.end();

	for( ; begin != end; ++begin )
	{
		if ( begin->second->m_pluginStatus == PluginData::State::Loaded )
		{
			begin->second->m_pluginPointer->close();
			begin->second->m_pluginStatus = PluginData::State::NotLoaded;
			begin->second->m_pluginPointer.reset();
		}
	}

} // PluginsManager::~PluginsManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBase >
PluginsManager::getPluginInterface( const unsigned int _pluginId, const unsigned int _interfaceId )
{
	PluginsCollectionTypeIterator iterator( m_pluginsCollection.find( _pluginId ) );

	if ( iterator == m_pluginsCollection.end() )
		return boost::intrusive_ptr< IBase >();

	switch ( iterator->second->m_pluginStatus )
	{
	case PluginData::State::Loaded:
		break;
	case PluginData::State::NotLoaded:
		loadPlugin( iterator->second );
		break;
	case PluginData::State::Loading:
		throw std::exception();				// Unsolvable situation
		break;
	default:
		assert( !"unsupported plugins status type!" );
		break;
	}

	return iterator->second->m_pluginPointer->getInterface( _interfaceId );

} // PluginsManager::getPluginInterface


/*---------------------------------------------------------------------------*/


bool
PluginsManager::isPluginLoaded( const unsigned int _pluginId ) const
{
	PluginsCollectionTypeIterator iterator( m_pluginsCollection.find( _pluginId ) );

	return
			( iterator != m_pluginsCollection.end() )
		&&	iterator->second->m_pluginStatus == PluginData::State::Loaded;

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
			loadPlugin( begin->second );
	}

} // PluginsManager::loadStartupPlugins


/*---------------------------------------------------------------------------*/


void
PluginsManager::loadPlugin( boost::shared_ptr< PluginData > _pluginData )
{
	_pluginData->m_pluginStatus = PluginData::State::Loading;

	PluginFactoryPtr connectorFactory
		= ( PluginFactoryPtr ) QLibrary::resolve(
				_pluginData->m_filePath.c_str()
			,	PluginFactoryName
			);
	assert( connectorFactory );
		
	_pluginData->m_pluginPointer.reset( connectorFactory() );
	assert( _pluginData->m_pluginPointer );

	_pluginData->m_pluginPointer->initialize( this );

	_pluginData->m_pluginStatus = PluginData::State::Loaded;

} // PluginsManager::loadPlugin


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
