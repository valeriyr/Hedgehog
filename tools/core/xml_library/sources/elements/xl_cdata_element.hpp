
#ifndef __XL_CDATA_ELEMENT_HPP__
#define __XL_CDATA_ELEMENT_HPP__

#include "xml_library/ih/xl_icdata_element.hpp"
#include "xml_library/sources/elements/xl_base_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class CDATAElement
	:	public BaseElement< ICDATAElement >
{

/*---------------------------------------------------------------------------*/

	typedef BaseElement< ICDATAElement > BaseType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CDATAElement();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_CDATA_ELEMENT_HPP__
