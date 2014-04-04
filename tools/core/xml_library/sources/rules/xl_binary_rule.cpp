
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


BinaryRule::BinaryRule( boost::shared_ptr< IElement > _element )
	:	m_element( _element )
{
} // BinaryRule::BinaryRule


/*---------------------------------------------------------------------------*/


BinaryRule::~BinaryRule()
{
} // BinaryRule::~BinaryRule


/*---------------------------------------------------------------------------*/


BinaryRule
BinaryRule::operator || ( const Tag& _tag )
{
	return BinaryRule( boost::shared_ptr< IElement >( new OrElement( m_element, _tag.getElement() ) ) );

} // BinaryRule::operator || ( const Tag& _tag )


/*---------------------------------------------------------------------------*/


boost::shared_ptr< IElement >
BinaryRule::getElement() const
{
	return m_element;

} // BinaryRule::getElement


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
