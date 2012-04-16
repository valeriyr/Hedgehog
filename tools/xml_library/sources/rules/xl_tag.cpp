
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_tag.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Tag::Tag( const QString& _tagName )
	:	BaseType( _tagName )
	,	m_childrenRule()
	,	m_attributeRule()
	,	m_repetMode( RepeatMode::Once )
{
} // Tag::Tag


/*---------------------------------------------------------------------------*/


void
Tag::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // Tag::accept


/*---------------------------------------------------------------------------*/


Tag&
Tag::operator[] ( const IRule& _rule )
{
	return *this;

} // Tag::operator[ const IRule& ]


/*---------------------------------------------------------------------------*/


Tag&
Tag::operator[] ( const IAttributeRule& _attributeRule )
{
	return *this;

} // Tag::operator[ const IAttributeRule& ]


/*---------------------------------------------------------------------------*/


Tag&
Tag::operator* ()
{
	m_repetMode = RepeatMode::ZeroOrAny;
	return *this;

} // Tag::operator*


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
