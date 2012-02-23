
/** Conector initializer interface */

#ifndef __CN_INITIALIZER_HPP_
#define __CN_INITIALIZER_HPP_

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


struct IInitializer
	:	public IBase
{
	virtual void initialize() = 0;
};


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_INITIALIZER_HPP_
