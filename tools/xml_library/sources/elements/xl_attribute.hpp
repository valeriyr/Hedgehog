
/** XML attribute declaration */

#ifndef __XL_ATTRIBUTE_HPP__
#define __XL_ATTRIBUTE_HPP__

#include "xml_library/ih/xl_iattribute.hpp"
#include "xml_library/sources/elements/xl_base_rule.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class Attribute
	:	public BaseRule< IAttribute >
{

/*---------------------------------------------------------------------------*/

	typedef BaseRule< IAttribute > BaseType;

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
