
#ifndef __CN_ILOADER_HPP__
#define __CN_ILOADER_HPP__

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

#endif // __CN_ILOADER_HPP__
