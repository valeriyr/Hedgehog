
#ifndef __XL_ATTRIBUTE_HPP__
#define __XL_ATTRIBUTE_HPP__

#include "xml_library/ih/xl_iattribute_rule.hpp"
#include "xml_library/sources/rules/xl_base_rule.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class Attribute
	:	public BaseRule< IAttributeRule >
{

/*---------------------------------------------------------------------------*/

	typedef BaseRule< IAttributeRule > BaseType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Attribute( const QString& _attributeName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ATTRIBUTE_HPP__
