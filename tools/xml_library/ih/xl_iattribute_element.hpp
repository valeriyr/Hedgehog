
#ifndef __XL_IATTRIBUTE_ELEMENT_HPP__
#define __XL_IATTRIBUTE_ELEMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "xml_library/ih/xl_ielement.hpp"

#include "xml_library/h/xl_attribute_type.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IAttributeElement
	:	public IElement
{
	virtual const std::string& getName() const = 0;

	virtual const AttributeType::Enum getType() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IATTRIBUTE_ELEMENT_HPP__
