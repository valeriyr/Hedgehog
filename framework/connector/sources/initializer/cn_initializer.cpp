
/** Connector initializer implementation part */

#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/initializer/cn_initializer.hpp"

#include "connector/h/cn_initializer_factory.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


Initializer::Initializer()
{
} // Initializer::Initializer


/*---------------------------------------------------------------------------*/


Initializer::~Initializer()
{
} // Initializer::~Initializer


/*---------------------------------------------------------------------------*/


void
Initializer::initialize()
{
} // Initializer::initialize


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IInitializer >
createInitializer()
{
	return boost::intrusive_ptr< IInitializer >( new Initializer() );

} // createInitializer


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
