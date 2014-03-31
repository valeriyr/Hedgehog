
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_base_element.hpp"

#include "xml_library/ih/xl_itag_element.hpp"
#include "xml_library/ih/xl_iattribute_element.hpp"
#include "xml_library/ih/xl_icdata_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


template < typename _TBaseInterface >
BaseElement< _TBaseInterface >::BaseElement( const QString& _name )
	:	m_name( _name )
{
} // BaseElement< _TBaseInterface >::BaseElement


/*---------------------------------------------------------------------------*/


template < typename _TBaseInterface >
const QString&
BaseElement< _TBaseInterface >::getName() const
{
	return m_name;

} // BaseElement< _TBaseInterface >::getName


/*---------------------------------------------------------------------------*/

template class BaseElement< ITagElement >;
template class BaseElement< IAttributeElement >;
template class BaseElement< ICDATAElement >;

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
