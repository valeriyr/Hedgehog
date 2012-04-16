
#ifndef __XL_IATTRIBUTE_RULE_HPP__
#define __XL_IATTRIBUTE_RULE_HPP__

/*---------------------------------------------------------------------------*/

#include "xml_library/ih/xl_irule.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class AndAttributeRule;

/*---------------------------------------------------------------------------*/

struct IAttributeRule
	:	public IRule
{
};

/*---------------------------------------------------------------------------*/

AndAttributeRule operator && ( const IAttributeRule& _first, const IAttributeRule& _second );

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IATTRIBUTE_RULE_HPP__
