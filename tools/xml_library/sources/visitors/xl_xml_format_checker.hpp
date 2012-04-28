
#ifndef __XL_XML_FORMAT_CHECKER_HPP__
#define __XL_XML_FORMAT_CHECKER_HPP__

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IElement;

/*---------------------------------------------------------------------------*/

class FormatChecker
	:	public IVisitor
{

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	FormatChecker();

	virtual ~FormatChecker();

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	static bool check ( const IElement& _element );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void visit ( const TagElement& _tag );

	/*virtual*/ void visit ( const AttributeElement& _attribute );

	/*virtual*/ void visit ( const AndElement& _andElement );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_XML_FORMAT_CHECKER_HPP__
