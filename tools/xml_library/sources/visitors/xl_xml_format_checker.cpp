
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/visitors/xl_xml_format_checker.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"
#include "xml_library/sources/elements/xl_tag_element.hpp"
#include "xml_library/sources/elements/xl_and_element.hpp"

#include "xml_library/sources/resources/xl_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


FormatChecker::FormatChecker()
	:	m_xmlSchemaDocument()
{
} // FormatChecker::FormatChecker


/*---------------------------------------------------------------------------*/


FormatChecker::~FormatChecker()
{
} // FormatChecker::~FormatChecker


/*---------------------------------------------------------------------------*/


bool
FormatChecker::check ( const IElement& _element, QIODevice& _ioDevise )
{
	_element.accept( *this );

	m_xmlSchemaDocument
		= QString( Resources::Strings::XmlSchemaDocumentFormat )
			.arg( m_xmlSchemaDocument );

	QXmlSchema schema;
	schema.load( m_xmlSchemaDocument );
	assert( schema.isValid() );

	QXmlSchemaValidator validator( schema );
	return validator.validate( &_ioDevise );

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


const QString&
FormatChecker::getXmlSchemaDocument() const
{
	return m_xmlSchemaDocument;

} // FormatChecker::getXmlSchemaDocument


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
