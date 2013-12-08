
#ifndef __LM_IACTION_HPP__
#define __LM_IACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct IAction
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void processAction( const unsigned int _deltaTime ) = 0;

	virtual void unprocessAction( const unsigned int _deltaTime ) = 0;

	virtual bool hasFinished() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IACTION_HPP__
