
/** XML element base implementation */

#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_element_base.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


BaseElement::BaseElement( const QString& _attributeName )
	:	m_attributeName( _attributeName )
{
} // Attribute::Attribute


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
