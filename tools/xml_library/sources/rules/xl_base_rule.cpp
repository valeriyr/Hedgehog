
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_base_rule.hpp"

#include "xml_library/ih/xl_itag_rule.hpp"
#include "xml_library/ih/xl_iattribute_rule.hpp"

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


template < typename _TBaseInterface >
const QString&
BaseRule< _TBaseInterface >::getName() const
{
	return m_name;

} // BaseRule< _TBaseInterface >::getName


/*---------------------------------------------------------------------------*/

template class BaseRule< ITagRule >;
template class BaseRule< IAttributeRule >;

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
