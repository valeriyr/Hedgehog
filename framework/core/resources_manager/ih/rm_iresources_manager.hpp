
#ifndef __RM_IRESOURCES_MANAGER_HPP__
#define __RM_IRESOURCES_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ResourcesManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_RESOURCES_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IResourcesManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual const QString& getString( const QString& _resourcePath ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ResourcesManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __RM_IRESOURCES_MANAGER_HPP__
