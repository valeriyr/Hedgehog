
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
	if ( _tag.getChildrenRule() )
		_tag.getChildrenRule()->accept( *this );

	if ( _tag.getAttributesRule() )
		_tag.getAttributesRule()->accept( *this );

	m_xmlSchemaDocument
		= QString( Resources::Strings::ElementFormat )
			.arg(
						_tag.getName().c_str()
					,		( _tag.getRepeatMode() == RepeatMode::ZeroAndMore )
						?	Resources::Strings::ZeroOrMoreRepeatElement
						:	""
					,	m_xmlSchemaDocument
					);

} // FormatChecker::visit


/*---------------------------------------------------------------------------*/


void
FormatChecker::visit ( const AttributeElement& _attribute )
{
	m_xmlSchemaDocument
		+= QString( Resources::Strings::AttributeFormat )
			.arg( _attribute.getName().c_str() );

} // FormatChecker::visit


/*---------------------------------------------------------------------------*/


void
FormatChecker::visit ( const AndElement& _andElement )
{
	_andElement.getLeft().accept( *this );
	_andElement.getRight().accept( *this );

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
