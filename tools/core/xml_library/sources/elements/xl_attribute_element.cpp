
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


AttributeElement::AttributeElement( const QString& _attributeName, AttributeType::Enum _attributeType )
	:	BaseType( _attributeName )
	,	m_attributeType( _attributeType ) 
{
} // AttributeElement::AttributeElement


/*---------------------------------------------------------------------------*/


void
AttributeElement::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // AttributeElement::accept


/*---------------------------------------------------------------------------*/


const AttributeType::Enum
AttributeElement::getType() const
{
	return m_attributeType;

} // AttributeElement::getType


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
