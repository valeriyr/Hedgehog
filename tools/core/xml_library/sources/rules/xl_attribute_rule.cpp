
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_attribute_rule.hpp"

#include "xml_library/sources/elements/xl_attribute_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Attribute::Attribute( const std::string& _name, AttributeType::Enum _type )
	:	BaseAttribute( boost::shared_ptr< IElement >( new AttributeElement( _name, _type ) ) )
{
} // Attribute::Attribute


/*---------------------------------------------------------------------------*/


Attribute::~Attribute()
{
} // Attribute::~Attribute


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
