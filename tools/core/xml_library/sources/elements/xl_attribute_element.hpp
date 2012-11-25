
#ifndef __XL_ATTRIBUTE_ELEMENT_HPP__
#define __XL_ATTRIBUTE_ELEMENT_HPP__

#include "xml_library/ih/xl_iattribute_element.hpp"
#include "xml_library/sources/elements/xl_base_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class AttributeElement
	:	public BaseElement< IAttributeElement >
{

/*---------------------------------------------------------------------------*/

	typedef BaseElement< IAttributeElement > BaseType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AttributeElement( const std::string& _attributeName, AttributeType::Enum _attributeType );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const AttributeType::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	AttributeType::Enum m_attributeType;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ATTRIBUTE_ELEMENT_HPP__
