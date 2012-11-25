
#ifndef __CN_ICONNECTOR_HPP__
#define __CN_ICONNECTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IConnector
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void initialize( const std::string& _pluginsDirectory ) = 0;

	virtual void close() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_ICONNECTOR_HPP__
