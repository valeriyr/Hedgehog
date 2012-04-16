
#ifndef __XL_TAG_HPP__
#define __XL_TAG_HPP__

#include "xml_library/ih/xl_itag_rule.hpp"
#include "xml_library/ih/xl_iattribute_rule.hpp"

#include "xml_library/sources/rules/xl_repeat_mode.hpp"

#include "xml_library/sources/rules/xl_base_rule.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class Tag
	:	public BaseRule< ITagRule >
{

/*---------------------------------------------------------------------------*/

	typedef BaseRule< ITagRule > BaseType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Tag( const QString& _tagName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

	// Set child elements rule
	Tag& operator[] ( const IRule& _rule );

	// Set attributes rule
	Tag& operator[] ( const IAttributeRule& _attributeRule );

	// Rule can be omitted or repeat any times
	Tag& operator* ();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::scoped_ptr< IRule > m_childrenRule;

	boost::scoped_ptr< IAttributeRule > m_attributeRule;

	RepeatMode::Enum m_repetMode;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_TAG_HPP__
