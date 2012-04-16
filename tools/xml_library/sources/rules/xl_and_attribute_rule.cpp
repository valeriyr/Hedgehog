
/** XML attribute implementation */

#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_and_attribute_rule.hpp"

#include "xml_library/sources/visitors/xl_copy_visitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


AndAttributeRule::AndAttributeRule( const IAttributeRule& _first, const IAttributeRule& _second )
	:	m_first( CopyVisitor< IAttributeRule >::copy( _first ).release() )
	,	m_second( CopyVisitor< IAttributeRule >::copy( _second ).release() )
{
} // AndAttributeRule::AndAttributeRule


/*---------------------------------------------------------------------------*/


void
AndAttributeRule::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // AndAttributeRule::accept


/*---------------------------------------------------------------------------*/


const IAttributeRule&
AndAttributeRule::getFirstArgument() const
{
	return *m_first;

} // AndAttributeRule::getFirstArgument


/*---------------------------------------------------------------------------*/


const IAttributeRule&
AndAttributeRule::getSecondArgument() const
{
	return *m_second;

} // AndAttributeRule::getSecondArgument


/*---------------------------------------------------------------------------*/


AndAttributeRule operator && ( const IAttributeRule& _first, const IAttributeRule& _second )
{
	return AndAttributeRule( _first, _second );

} // operator &&


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
