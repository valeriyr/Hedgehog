
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_base_attribute_rule.hpp"

#include "xml_library/sources/elements/xl_and_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


BaseAttribute::BaseAttribute( boost::shared_ptr< IElement > _element )
	:	m_element( _element )
{
} // BaseAttribute::BaseAttribute


/*---------------------------------------------------------------------------*/


BaseAttribute::~BaseAttribute()
{
} // BaseAttribute::~BaseAttribute


/*---------------------------------------------------------------------------*/


boost::shared_ptr< IElement >
BaseAttribute::getElement() const
{
	return m_element;

} // Attribute::getElement


/*---------------------------------------------------------------------------*/


BaseAttribute&
BaseAttribute::operator && ( const BaseAttribute& _attribute )
{
	m_element.reset( new AndElement( m_element, _attribute.getElement() ) );
	return *this;

} // BaseAttribute::operator &&


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
