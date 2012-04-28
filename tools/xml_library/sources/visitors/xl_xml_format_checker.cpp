
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/visitors/xl_xml_format_checker.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"
#include "xml_library/sources/elements/xl_tag_element.hpp"
#include "xml_library/sources/elements/xl_and_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


FormatChecker::FormatChecker()
{
} // FormatChecker::FormatChecker


/*---------------------------------------------------------------------------*/


FormatChecker::~FormatChecker()
{
} // FormatChecker::~FormatChecker


/*---------------------------------------------------------------------------*/


bool
FormatChecker::check ( const IElement& _element )
{
	return true;

} // FormatChecker::parse


/*---------------------------------------------------------------------------*/


void
FormatChecker::visit ( const TagElement& _tag )
{
} // FormatChecker::visit


/*---------------------------------------------------------------------------*/


void
FormatChecker::visit ( const AttributeElement& _attribute )
{
} // FormatChecker::visit


/*---------------------------------------------------------------------------*/


void
FormatChecker::visit ( const AndElement& _andElement )
{
} // FormatChecker::visit


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
