
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_attribute_rule.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Attribute::Attribute( const std::string& _name )
	:	m_attributeElement( new AttributeElement( _name ) )
{
} // Attribute::Attribute


/*---------------------------------------------------------------------------*/


Attribute::~Attribute()
{
} // Attribute::~Attribute


/*---------------------------------------------------------------------------*/


boost::shared_ptr< IElement >
Attribute::getElement() const
{
	return m_attributeElement;

} // Attribute::getElement


/*---------------------------------------------------------------------------*/


Attribute&
Attribute::operator && ( const Attribute& _attribute )
{
	return *this;

} // Attribute::operator &&


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
