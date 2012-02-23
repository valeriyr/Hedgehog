
/** Connector initializer factory */

#ifndef __CN_INITIALIZER_FACTORY_HPP_
#define __CN_INITIALIZER_FACTORY_HPP_

/*---------------------------------------------------------------------------*/

#include "connector/h/cn_export.hpp"
#include "connector/ih/cn_iinitializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


	CONNECTOR_EXPORT
		boost::intrusive_ptr< IInitializer >
		createInitializer();


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_INITIALIZER_FACTORY_HPP_
