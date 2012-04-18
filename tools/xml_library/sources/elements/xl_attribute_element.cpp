
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


AttributeElement::AttributeElement( const std::string& _attributeName )
	:	BaseType( _attributeName )
{
} // AttributeElement::AttributeElement


/*---------------------------------------------------------------------------*/


void
AttributeElement::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // AttributeElement::accept


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
