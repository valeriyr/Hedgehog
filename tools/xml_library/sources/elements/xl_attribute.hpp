
/** XML attribute declaration */

#ifndef __XL_ATTRIBUTE_HPP__
#define __XL_ATTRIBUTE_HPP__

#include "xml_library/sources/elements/xl_element_base.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class Attribute
	:	public BaseElement
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Attribute( const QString& _attributeName );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ATTRIBUTE_HPP__
