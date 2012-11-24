
#ifndef __XL_ATTRIBUTE_RULE_HPP__
#define __XL_ATTRIBUTE_RULE_HPP__

#include "xml_library/sources/rules/xl_base_attribute_rule.hpp"

#include "xml_library/h/xl_attribute_type.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class AttributeElement;

/*---------------------------------------------------------------------------*/

class Attribute
	:	public BaseAttribute
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Attribute( const std::string& _name, AttributeType::Enum _type );

	virtual ~Attribute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ATTRIBUTE_RULE_HPP__
