
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/visitors/xl_xml_parser.hpp"

#include "xml_library/sources/visitors/xl_xml_format_checker.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"
#include "xml_library/sources/elements/xl_tag_element.hpp"
#include "xml_library/sources/elements/xl_and_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Parser::Parser()
{
} // Parser::Parser


/*---------------------------------------------------------------------------*/


Parser::~Parser()
{
} // Parser::~Parser


/*---------------------------------------------------------------------------*/


void
Parser::parse ( const IElement& _element, QIODevice& _ioDevise )
{
	QDomDocument document;

	if ( !document.setContent( &_ioDevise, false ) )
		return;

	if ( !FormatChecker::check( _element ) )
		return;

	Parser parser;
	_element.accept( parser );

} // Parser::parse


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const TagElement& _tag )
{
} // Parser::visit


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const AttributeElement& _attribute )
{
} // Parser::visit


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const AndElement& _andElement )
{
} // Parser::visit


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
