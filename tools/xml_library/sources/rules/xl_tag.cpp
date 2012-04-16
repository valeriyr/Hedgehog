
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_tag.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Tag::Tag( const QString& _tagName )
	:	BaseType( _tagName )
{
} // Tag::Tag


/*---------------------------------------------------------------------------*/


void
Tag::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // Tag::accept


/*---------------------------------------------------------------------------*/


ITagRule&
Tag::operator[] ( const IRule& _rule )
{
	return *this;

} // Tag::operator[ const IRule& ]


/*---------------------------------------------------------------------------*/


ITagRule&
Tag::operator[] ( const IAttributeRule& _attributeRule )
{
	return *this;

} // Tag::operator[ const IAttributeRule& ]


/*---------------------------------------------------------------------------*/


ITagRule&
Tag::operator* ()
{
	return *this;

} // Tag::operator*


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
