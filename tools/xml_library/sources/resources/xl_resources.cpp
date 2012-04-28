
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

	const char* const ComplexTypeFormat = "<xsd::complexType>%2</xsd::complexType>";

	const char* const ElementFormat = "<xsd::element name=\"%1\"/>";

/*---------------------------------------------------------------------------*/

} // namespace Strings

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
