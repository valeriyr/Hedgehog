
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_cdata_element.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


CDATAElement::CDATAElement()
	:	BaseType( "CDATA" )
{
} // CDATAElement::CDATAElement


/*---------------------------------------------------------------------------*/


void
CDATAElement::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // CDATAElement::accept


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
