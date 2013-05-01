
#ifndef __GM_IGAME_MANAGER_HPP__
#define __GM_IGAME_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct IUnit;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


struct IGameManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void pushMoveAction( boost::intrusive_ptr< LandscapeModel::IUnit > _unit ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_IGAME_MANAGER_HPP__
