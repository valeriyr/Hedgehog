
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_or_element.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


OrElement::OrElement(
		boost::shared_ptr< IElement > _left
	,	boost::shared_ptr< IElement > _right
	)
	:	BinaryElement( _left, _right )
{
} // OrElement::OrElement


/*---------------------------------------------------------------------------*/


void
OrElement::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // OrElement::accept


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
