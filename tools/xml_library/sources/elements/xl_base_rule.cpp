
/** XML element base implementation */

#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_base_rule.hpp"

#include "xml_library/ih/xl_itag.hpp"
#include "xml_library/ih/xl_iattribute.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


template < typename _TBaseInterface >
BaseRule< _TBaseInterface >::BaseRule( const QString& _name )
	:	m_name( _name )
{
} // BaseRule< _TBaseInterface >::BaseRule


/*---------------------------------------------------------------------------*/

template class BaseRule< ITag >;
template class BaseRule< IAttribute >;

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
