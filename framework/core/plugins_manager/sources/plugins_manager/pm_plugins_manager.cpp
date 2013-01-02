
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/plugins_manager/pm_plugins_manager.hpp"

#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "plugins_manager/sources/plugins_manager/pm_plugin_data.hpp"
#include "plugins_manager/sources/resources/pm_internal_resources.hpp"

#include "messenger/ms_imessenger.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


PluginsManager::PluginsManager( boost::intrusive_ptr< ISystemInformation > _systemInformation )
	:	m_pluginsCollection()
	,	m_pluginsInLoadingOrderCollection()
	,	m_systemInformation( _systemInformation )
{
} // PluginsManager::PluginsManager


/*---------------------------------------------------------------------------*/


PluginsManager::~PluginsManager()
{
} // PluginsManager::~PluginsManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Tools::Core::IBase >
PluginsManager::getPluginInterface( const QString& _pluginName, const unsigned int _interfaceId )
{
	if ( _pluginName == PID_PLUGINS_MANAGER )
	{
		switch( _interfaceId )
		{
		case IID_SYSTEM_INFORMATION:
			return m_systemInformation;
		case Tools::Core::IID_MESSENGER:
			return getPluginInterface( m_systemInformation->getSystemMessengerPluginName(), _interfaceId );
		default:
			return boost::intrusive_ptr< Tools::Core::IBase >();
		}
	}

	PluginsCollectionTypeIterator iterator( m_pluginsCollection.find( _pluginName ) );

	if (	iterator == m_pluginsCollection.end()
		||	( iterator->second->m_pluginState == PluginData::State::Closed )
		)
	{
		return boost::intrusive_ptr< IBase >();
	}

	if ( iterator->second->m_pluginState == PluginData::State::Loading )	// We can't get interface from plugin
		throw std::exception();												// witch is loading!

	loadPluginIfNeeded( iterator->second );

	return iterator->second->m_pluginPointer->getInterface( _interfaceId );

} // PluginsManager::getPluginInterface


/*---------------------------------------------------------------------------*/


bool
PluginsManager::isPluginLoaded( const QString& _pluginName ) const
{
	if ( _pluginName == PID_PLUGINS_MANAGER )
		return true;

	PluginsCollectionTypeIterator iterator( m_pluginsCollection.find( _pluginName ) );

	return
			( iterator != m_pluginsCollection.end() )
		&&	iterator->second->m_pluginState == PluginData::State::Loaded;

} // PluginsManager::isPluginLoaded


/*---------------------------------------------------------------------------*/


void
PluginsManager::registerPlugin( boost::shared_ptr< PluginData > _pluginData )
{
	assert( _pluginData );
	assert( m_pluginsCollection.find( _pluginData->m_pluginName ) == m_pluginsCollection.end() );

	m_pluginsCollection.insert( std::make_pair( _pluginData->m_pluginName, _pluginData ) );

} // PluginsManager::registerPlugin


/*---------------------------------------------------------------------------*/


void
PluginsManager::loadPlugins()
{
	PluginsCollectionTypeIterator
			begin = m_pluginsCollection.begin()
		,	end = m_pluginsCollection.end();

	for( ; begin != end; ++begin )
		loadPluginIfNeeded( begin->second );

} // PluginsManager::loadStartupPlugins


/*---------------------------------------------------------------------------*/


void
PluginsManager::closePlugins()
{
	PluginsInLoadingOrderCollectionTypeIterator
			begin = m_pluginsInLoadingOrderCollection.rbegin()
		,	end = m_pluginsInLoadingOrderCollection.rend();

	for( ; begin != end; ++begin )
	{
		assert( ( *begin )->m_pluginState == PluginData::State::Loaded );

		( *begin )->m_pluginPointer->close();
		( *begin )->m_pluginPointer.reset();

		( *begin )->m_pluginState = PluginData::State::Closed;
	}

	m_pluginsInLoadingOrderCollection.clear();

} // PluginsManager::closePlugins


/*---------------------------------------------------------------------------*/


void
PluginsManager::loadPluginIfNeeded( boost::shared_ptr< PluginData > _pluginData )
{
	if ( _pluginData->m_pluginState == PluginData::State::NotLoaded )
	{
		_pluginData->m_pluginState = PluginData::State::Loading;

		QString pluginPath(
				m_systemInformation->getPluginsDirectory()
			+	"/"
			+	_pluginData->m_pluginName
			+	Resources::PluginFileExtension );

		PluginFactoryPtr pluginFactory
			= ( PluginFactoryPtr ) QLibrary::resolve( pluginPath, PluginFactoryName );
		assert( pluginFactory );

		_pluginData->m_pluginPointer.reset( pluginFactory() );
		assert( _pluginData->m_pluginPointer );

		_pluginData->m_pluginPointer->initialize( this );

		m_pluginsInLoadingOrderCollection.push_back( _pluginData );

		_pluginData->m_pluginState = PluginData::State::Loaded;
	}

} // PluginsManager::loadPluginIfNeeded


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
