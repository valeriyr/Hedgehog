
#ifndef __XL_ITAG_HPP__
#define __XL_ITAG_HPP__

/*---------------------------------------------------------------------------*/

#include "xml_library/ih/xl_irule.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

	struct IAttribute;
	struct IAttributeRule;

/*---------------------------------------------------------------------------*/

struct ITagRule
	:	public IRule
{

/*---------------------------------------------------------------------------*/

	// Set child elements rule
	virtual ITagRule& operator[] ( const IRule& _rule ) = 0;

	// Set attributes rule
	virtual ITagRule& operator[] ( const IAttributeRule& _attributeRule ) = 0;

	// Rule can be omitted or repeat any times
	virtual ITagRule& operator* () = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ITAG_HPP__
