
/** Connector initializer implementation part */

#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/initializer/cn_initializer.hpp"

#include "connector/h/cn_initializer_factory.hpp"

#include "connector/sources/plugin/cn_plugin_instance.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


Initializer::Initializer()
	:	m_connector( createPlugin() )
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
	m_connector->initialize( NULL );

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
