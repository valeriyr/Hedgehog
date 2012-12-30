
#include "resources_manager/sources/ph/rm_ph.hpp"

#include "resources_manager/sources/resources_manager/rm_resources_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ResourcesManager {

/*---------------------------------------------------------------------------*/


ResourcesManager::ResourcesManager( const QString& _resourcesDirectory )
	:	m_resourcesDirectory( _resourcesDirectory )
{
} // ResourcesManager::ResourcesManager


/*---------------------------------------------------------------------------*/


ResourcesManager::~ResourcesManager()
{
} // ResourcesManager::~ResourcesManager


/*---------------------------------------------------------------------------*/


const QString&
ResourcesManager::getString( const QString& _resourcePath )
{
	return m_resourcesDirectory;

} // ResourcesManager::getString


/*---------------------------------------------------------------------------*/

} // namespace ResourcesManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
