
#ifndef __LM_IAI_MANAGER_HPP__
#define __LM_IAI_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IAiManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void regAi( const QString& _name, const QString& _race ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IAI_MANAGER_HPP__
