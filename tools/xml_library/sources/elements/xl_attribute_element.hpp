
#ifndef __XL_ATTRIBUTE_ELEMENT_HPP__
#define __XL_ATTRIBUTE_ELEMENT_HPP__

#include "xml_library/ih/xl_iattribute_element.hpp"
#include "xml_library/sources/elements/xl_base_element.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
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

	AttributeElement( const std::string& _attributeName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ATTRIBUTE_ELEMENT_HPP__
