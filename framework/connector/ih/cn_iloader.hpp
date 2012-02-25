
/** Conector loader interface */

#ifndef __CN_ILOADER_HPP_
#define __CN_ILOADER_HPP_

/*---------------------------------------------------------------------------*/

#include "connector/h/cn_export.hpp"
#include "connector/ih/cn_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


struct ILoader
	:	public IBase
{
	virtual void load() = 0;

	virtual void unload() = 0;
};


/*---------------------------------------------------------------------------*/

CONNECTOR_EXPORT
		boost::intrusive_ptr< ILoader >
		createLoader();

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IAUTO_LOADER_HPP_
