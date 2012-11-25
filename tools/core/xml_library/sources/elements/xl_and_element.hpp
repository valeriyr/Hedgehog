
#ifndef __XL_AND_ELEMENT_HPP__
#define __XL_AND_ELEMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "xml_library/sources/elements/xl_binary_element.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


class AndElement
	:	public BinaryElement
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AndElement(
			boost::shared_ptr< IElement > _left
		,	boost::shared_ptr< IElement > _right
		);

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_AND_ELEMENT_HPP__
