
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/resources_manager/mm_resources_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


ResourcesManager::ResourcesManager()
	:	m_resourcesCollection()
	,	m_internalMutex()
{
} // ResourcesManager::ResourcesManager


/*---------------------------------------------------------------------------*/


ResourcesManager::~ResourcesManager()
{
} // ResourcesManager::~ResourcesManager


/*---------------------------------------------------------------------------*/


void
ResourcesManager::registerResource( const QString& _resourceName )
{
	QWriteLocker locker( &m_internalMutex );

	assert( m_resourcesCollection.find( _resourceName ) == m_resourcesCollection.end() );

	m_resourcesCollection.insert(
		std::make_pair(
				_resourceName
			,	boost::shared_ptr< LockData >( new LockData() ) ) );

} // ResourcesManager::registerResource


/*---------------------------------------------------------------------------*/


void
ResourcesManager::unregisterResource( const QString& _resourceName )
{
	QWriteLocker locker( &m_internalMutex );

	assert( m_resourcesCollection.find( _resourceName ) != m_resourcesCollection.end() );

	m_resourcesCollection.erase( _resourceName );

} // ResourcesManager::unregisterResource


/*---------------------------------------------------------------------------*/


bool
ResourcesManager::tryLock(
		const QString& _resourceName
	,	const IResourcesManager::AccessType::Enum _lockType
	,	const int _timeout )
{
	if ( _lockType == IResourcesManager::AccessType::Unlocked )
		return false;

	QWriteLocker locker( &m_internalMutex );

	boost::shared_ptr< ResourcesManager::LockData > lockData = getLockData( _resourceName );

	bool result = false;

	if ( _lockType == IResourcesManager::AccessType::Read )
		result = lockData->m_mutex.tryLockForRead();
	else if ( _lockType == IResourcesManager::AccessType::Write )
		result = lockData->m_mutex.tryLockForWrite();

	if ( result )
	{
		lockData->m_accessType = _lockType;
	}

	return result;

} // ResourcesManager::tryLock


/*---------------------------------------------------------------------------*/


void
ResourcesManager::lock(
		const QString& _resourceName
	,	const IResourcesManager::AccessType::Enum _lockType )
{
	if ( _lockType == IResourcesManager::AccessType::Unlocked )
		return;

	QWriteLocker locker( &m_internalMutex );

	boost::shared_ptr< ResourcesManager::LockData > lockData = getLockData( _resourceName );

	if ( _lockType == IResourcesManager::AccessType::Read )
		lockData->m_mutex.lockForRead();
	else if ( _lockType == IResourcesManager::AccessType::Write )
		lockData->m_mutex.lockForWrite();

	lockData->m_accessType = _lockType;

} // ResourcesManager::lock


/*---------------------------------------------------------------------------*/


void
ResourcesManager::unlock( const QString& _resourceName )
{
	QWriteLocker locker( &m_internalMutex );

	boost::shared_ptr< ResourcesManager::LockData > lockData = getLockData( _resourceName );

	lockData->m_mutex.unlock();
	lockData->m_accessType = IResourcesManager::AccessType::Unlocked;

} // ResourcesManager::unlock


/*---------------------------------------------------------------------------*/


IResourcesManager::AccessType::Enum
ResourcesManager::getResourceStatus( const QString& _resourceName )
{
	QReadLocker locker( &m_internalMutex );

	boost::shared_ptr< ResourcesManager::LockData > lockData = getLockData( _resourceName );

	return lockData->m_accessType;

} // ResourcesManager::getResourceStatus


/*---------------------------------------------------------------------------*/


boost::shared_ptr< ResourcesManager::LockData >
ResourcesManager::getLockData( const QString& _resourceName ) const
{
	ResourcesCollectionConstIterator iterator = m_resourcesCollection.find( _resourceName );

	if ( iterator != m_resourcesCollection.end() )
		return iterator->second;

	return boost::shared_ptr< LockData >();

} // ResourcesManager::getLockData


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
