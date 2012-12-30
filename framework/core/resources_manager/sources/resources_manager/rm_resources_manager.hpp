
#ifndef __RM_RESOURCES_MANAGER_HPP__
#define __RM_RESOURCES_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "resources_manager/ih/rm_iresources_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ResourcesManager {

/*---------------------------------------------------------------------------*/

class ResourcesManager
	:	public Tools::Core::BaseWrapper< IResourcesManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ResourcesManager( const QString& _resourcesDirectory );

	virtual ~ResourcesManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getString( const QString& _resourcePath );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QString m_resourcesDirectory;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ResourcesManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __RM_RESOURCES_MANAGER_HPP__
