
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/visitors/xl_xml_parser.hpp"

#include "xml_library/sources/visitors/xl_xml_format_checker.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"
#include "xml_library/sources/elements/xl_tag_element.hpp"
#include "xml_library/sources/elements/xl_and_element.hpp"
#include "xml_library/sources/elements/xl_or_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Parser::Parser( QDomElement& _domElement )
	:	m_domElement( _domElement )
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
	FormatChecker checker;
	if ( !checker.check( _element, _ioDevise ) )
		return;

	QDomDocument document;
	if ( !document.setContent( &_ioDevise, false ) )
		return;

	Parser parser( document.documentElement() );
	_element.accept( parser );

} // Parser::parse


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const TagElement& _tag )
{
	if ( _tag.getName() != m_domElement.tagName() )
		return;

	TagElement::HandlesCollectionIteratorTypePtr handlesIterator( _tag.getHandles() );

	while ( handlesIterator->isValid() )
	{
		( *handlesIterator->current() )( m_domElement );
		handlesIterator->next();
	}

	if ( _tag.getChildrenRule() )
	{
		QDomElement childElement( m_domElement.firstChildElement() );

		while( !childElement.isNull() )
		{
			Parser parser( childElement );
			_tag.getChildrenRule()->accept( parser );

			childElement = childElement.nextSiblingElement();
		}
	}

	TagElement::HandlesCollectionIteratorTypePtr postHandlesIterator( _tag.getPostHandles() );

	while ( postHandlesIterator->isValid() )
	{
		( *postHandlesIterator->current() )( m_domElement );
		postHandlesIterator->next();
	}

} // Parser::visit


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const AttributeElement& _attribute )
{
} // Parser::visit


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const CDATAElement& _cdataElement )
{
} // Parser::visit


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const AndElement& _andElement )
{
	Parser parserForLeftElement( m_domElement );
	_andElement.getLeft().accept( parserForLeftElement );

	Parser parserForRightElement( m_domElement );
	_andElement.getRight().accept( parserForRightElement );

} // Parser::visit


/*---------------------------------------------------------------------------*/


void
Parser::visit ( const OrElement& _orElement )
{
	Parser parserForLeftElement( m_domElement );
	_orElement.getLeft().accept( parserForLeftElement );

	Parser parserForRightElement( m_domElement );
	_orElement.getRight().accept( parserForRightElement );

} // Parser::visit


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
