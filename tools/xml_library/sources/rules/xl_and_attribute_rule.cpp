
/** XML attribute implementation */

#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_and_attribute_rule.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


AndAttributeRule::AndAttributeRule( const IAttributeRule& _first, const IAttributeRule& _second )
	:	m_first( _first )
	,	m_second( _second )
{
} // AndAttributeRule::AndAttributeRule


/*---------------------------------------------------------------------------*/


void
AndAttributeRule::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // AndAttributeRule::accept


/*---------------------------------------------------------------------------*/


IAttributeRule& operator && ( const IAttributeRule& _first, const IAttributeRule& _second )
{
	return AndAttributeRule( _first, _second );

} // operator &&


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
