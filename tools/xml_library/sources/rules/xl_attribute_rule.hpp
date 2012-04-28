
#ifndef __XL_ATTRIBUTE_RULE_HPP__
#define __XL_ATTRIBUTE_RULE_HPP__

#include "xml_library/sources/rules/xl_rule.hpp"

#include "xml_library/sources/rules/xl_base_attribute_rule.hpp"


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

	Attribute( const std::string& _name );

	virtual ~Attribute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ATTRIBUTE_RULE_HPP__
