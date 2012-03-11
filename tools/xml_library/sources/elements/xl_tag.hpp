
/** XML tag declaration */

#ifndef __XL_TAG_HPP__
#define __XL_TAG_HPP__

#include "xml_library/ih/xl_itag.hpp"
#include "xml_library/sources/elements/xl_base_rule.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class Tag
	:	public BaseRule< ITag >
{

/*---------------------------------------------------------------------------*/

	typedef BaseRule< ITag > BaseType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Tag( const QString& _tagName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

	// Set child elements rule
	/*virtual*/ ITag& operator[] ( const IRule& _rule );

	// Set attributes rule
	/*virtual*/ ITag& operator[] ( const IAttributeRule& _attributeRule );

	// Rule can be omitted or repeat any times
	/*virtual*/ ITag& operator* ();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_TAG_HPP__
