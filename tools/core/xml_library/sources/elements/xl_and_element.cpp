
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_and_element.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


AndElement::AndElement(
		boost::shared_ptr< IElement > _left
	,	boost::shared_ptr< IElement > _right
	)
	:	BinaryElement( _left, _right )
{
} // AndElement::AndElement


/*---------------------------------------------------------------------------*/


void
AndElement::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // AndElement::accept


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
