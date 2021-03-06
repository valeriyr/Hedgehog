
#ifndef __XL_BASE_ATTRIBUTE_RULE_HPP__
#define __XL_BASE_ATTRIBUTE_RULE_HPP__

#include "xml_library/sources/rules/xl_rule.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class BaseAttribute
	:	public Rule
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseAttribute( boost::shared_ptr< IElement > _element );

	virtual ~BaseAttribute();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< IElement > getElement() const;

/*---------------------------------------------------------------------------*/

	BaseAttribute& operator && ( const BaseAttribute& _attribute );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< IElement > m_element;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_BASE_ATTRIBUTE_RULE_HPP__
