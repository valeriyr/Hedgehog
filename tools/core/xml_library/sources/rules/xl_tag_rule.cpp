
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_tag_rule.hpp"

#include "xml_library/sources/rules/xl_attribute_rule.hpp"

#include "xml_library/sources/elements/xl_tag_element.hpp"
#include "xml_library/sources/elements/xl_or_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Tag::Tag( const QString& _name )
	:	m_tagElement( new TagElement( _name ) )
{
} // Tag::Tag


/*---------------------------------------------------------------------------*/


Tag::~Tag()
{
} // Tag::~Tag


/*---------------------------------------------------------------------------*/


boost::shared_ptr< IElement >
Tag::getElement() const
{
	return m_tagElement;

} // Tag::getElement


/*---------------------------------------------------------------------------*/


Tag&
Tag::operator [] ( const Rule& _rule )
{
	m_tagElement->setChildrenRule( _rule.getElement() );
	return *this;

} // Tag::operator [] ( const Rule& _rule )


/*---------------------------------------------------------------------------*/


Tag&
Tag::operator [] ( const Attribute& _attribute )
{
	m_tagElement->setAttributesRule( _attribute.getElement() );
	return *this;

} // Tag::operator [] ( const Attribute& _attribute )


/*---------------------------------------------------------------------------*/


Tag&
Tag::operator * ()
{
	m_tagElement->setRepeatMode( RepeatMode::ZeroAndMore );
	return *this;

} // Tag::operator *


/*---------------------------------------------------------------------------*/


Tag&
Tag::operator + ()
{
	m_tagElement->setRepeatMode( RepeatMode::OneOrMore );
	return *this;

} // Tag::operator +


/*---------------------------------------------------------------------------*/


BinaryRule
Tag::operator || ( const Tag& _tag )
{
	return BinaryRule( boost::shared_ptr< IElement >( new OrElement( m_tagElement, _tag.getElement() ) ) );

} // Tag::operator &&


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
