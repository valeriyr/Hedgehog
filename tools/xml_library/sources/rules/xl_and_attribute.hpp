
#ifndef __XL_AND_ATTRIBUTE_HPP__
#define __XL_AND_ATTRIBUTE_HPP__

#include "xml_library/ih/xl_iattribute_rule.hpp"
#include "xml_library/sources/rules/xl_and_rule.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

	typedef
		AndRule< IAttributeRule >
		AndAttribute;

	AndAttribute operator && ( const IAttributeRule& _left, const IAttributeRule& _right );

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_AND_ATTRIBUTE_HPP__
