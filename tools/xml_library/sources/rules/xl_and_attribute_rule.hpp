
/** And attribute rule declaration */

#ifndef __XL_AND_ATTRIBUTE_RULE_HPP__
#define __XL_AND_ATTRIBUTE_RULE_HPP__

#include "xml_library/ih/xl_iattribute_rule.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class AndAttributeRule
	:	public IAttributeRule
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AndAttributeRule( const IAttributeRule& _first, const IAttributeRule& _second );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IAttributeRule& m_first;

	const IAttributeRule& m_second;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_AND_ATTRIBUTE_RULE_HPP__
