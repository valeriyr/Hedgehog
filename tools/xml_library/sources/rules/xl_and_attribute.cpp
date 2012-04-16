
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_and_attribute.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


AndAttribute
operator && ( const IAttributeRule& _left, const IAttributeRule& _right )
{
	return AndAttribute( _left, _right );

} // operator &&


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
