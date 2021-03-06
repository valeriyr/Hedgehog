
#ifndef __XL_BINARY_ELEMENT_HPP__
#define __XL_BINARY_ELEMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "xml_library/ih/xl_iattribute_element.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


class BinaryElement
	:	public IElement
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BinaryElement(
			boost::shared_ptr< IElement > _left
		,	boost::shared_ptr< IElement > _right
		);

/*---------------------------------------------------------------------------*/

	const IElement& getLeft() const;

	const IElement& getRight() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< IElement > m_left;

	boost::shared_ptr< IElement > m_right;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_BINARY_ELEMENT_HPP__
