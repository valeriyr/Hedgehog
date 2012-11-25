
#ifndef __CN_ILOADER_HPP__
#define __CN_ILOADER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/h/cn_export.hpp"
#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/


struct ILoader
	:	public Tools::Core::IBase
{
	virtual void load( const std::string& _pluginsDirectory ) = 0;

	virtual void unload() = 0;
};


/*---------------------------------------------------------------------------*/

CONNECTOR_EXPORT
		boost::intrusive_ptr< ILoader >
		createLoader();

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_ILOADER_HPP__
