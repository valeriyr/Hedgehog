
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

	const IAttributeRule& getFirstArgument() const;

	const IAttributeRule& getSecondArgument() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::scoped_ptr< IAttributeRule > m_first;

	boost::scoped_ptr< IAttributeRule > m_second;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_AND_ATTRIBUTE_RULE_HPP__
