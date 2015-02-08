
#ifndef __MM_IRESOURCES_MANAGER_HPP__
#define __MM_IRESOURCES_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

	const quint32 IID_RESOURCES_MANAGER = 1;

/*---------------------------------------------------------------------------*/

struct IResourcesManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct AccessType
	{
		enum Enum
		{
				Unlocked = 0

			,	Read = 1
			,	Write = 2
		};
	};

/*---------------------------------------------------------------------------*/

	virtual void registerResource( const QString& _resourceName ) = 0;

	virtual void unregisterResource( const QString& _resourceName ) = 0;

/*---------------------------------------------------------------------------*/

	virtual bool tryLock(
			const QString& _resourceName
		,	const AccessType::Enum _lockType
		,	const int _timeout ) = 0;

	virtual void lock(
			const QString& _resourceName
		,	const AccessType::Enum _lockType ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void unlock( const QString& _resourceName ) = 0;

/*---------------------------------------------------------------------------*/

	virtual AccessType::Enum getResourceStatus( const QString& _resourceName ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_IRESOURCES_MANAGER_HPP__
