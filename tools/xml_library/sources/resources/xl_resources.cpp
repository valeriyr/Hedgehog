
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/resources/xl_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {
namespace Resources {

/*---------------------------------------------------------------------------*/

namespace Strings {

/*---------------------------------------------------------------------------*/

	const char* const XmlSchemaDocumentFormat = "<?xml version=\"1.0\" encoding=\"utf-8\"?><xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">%1</xsd:schema>";

	const char* const ElementFormat = "<xsd:element name=\"%1\" %2><xsd:complexType><xsd:sequence>%3</xsd:sequence></xsd:complexType></xsd:element>";

	const char* const ZeroOrMoreRepeatElement = "minOccurs=\"0\" maxOccurs=\"unbounded\"";

	const char* const AttributeFormat = "<xsd:attribute name=\"%1\" use=\"required\"/>";

/*---------------------------------------------------------------------------*/

} // namespace Strings

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
