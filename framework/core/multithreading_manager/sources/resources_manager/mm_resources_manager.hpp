
#ifndef __MM_RESOURCES_MANAGER_HPP__
#define __MM_RESOURCES_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/ih/mm_iresources_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

class ResourcesManager
	:	public Tools::Core::BaseWrapper< IResourcesManager >
{

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct LockData
	{
		LockData()
			:	m_mutex()
			,	m_accessType( IResourcesManager::AccessType::Unlocked )
		{}

		QReadWriteLock m_mutex;
		IResourcesManager::AccessType::Enum m_accessType;
	};

	typedef
		std::map< QString, boost::shared_ptr< LockData > >
		ResourcesCollection;
	typedef
		ResourcesCollection::iterator
		ResourcesCollectionIterator;
	typedef
		ResourcesCollection::const_iterator
		ResourcesCollectionConstIterator;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ResourcesManager();

	virtual ~ResourcesManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void registerResource( const QString& _resourceName );

	/*virtual*/ void unregisterResource( const QString& _resourceName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool tryLock(
			const QString& _resourceName
		,	const IResourcesManager::AccessType::Enum _lockType
		,	const int _timeout );

	/*virtual*/ void lock(
			const QString& _resourceName
		,	const IResourcesManager::AccessType::Enum _lockType );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void unlock( const QString& _resourceName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ IResourcesManager::AccessType::Enum getResourceStatus( const QString& _resourceName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< LockData > getLockData( const QString& _resourceName ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	ResourcesCollection m_resourcesCollection;

	QReadWriteLock m_internalMutex;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_RESOURCES_MANAGER_HPP__
