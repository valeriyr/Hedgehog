
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_and_rule.hpp"

#include "xml_library/ih/xl_iattribute_rule.hpp"
#include "xml_library/sources/visitors/xl_copy_visitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


template< typename _TBase >
AndRule< _TBase >::AndRule( const _TBase& _left, const _TBase& _right )
	:	m_left( CopyVisitor< _TBase >::copy( _left ).release() )
	,	m_right( CopyVisitor< _TBase >::copy( _right ).release() )
{
} // AndRule< _TBase >::AndRule


/*---------------------------------------------------------------------------*/


template< typename _TBase >
void
AndRule< _TBase >::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // AndRule< _TBase >::accept


/*---------------------------------------------------------------------------*/


template< typename _TBase >
const _TBase&
AndRule< _TBase >::getLeft() const
{
	return *m_left;

} // AndRule< _TBase >::getLeft


/*---------------------------------------------------------------------------*/


template< typename _TBase >
const _TBase&
AndRule< _TBase >::getRight() const
{
	return *m_right;

} // AndRule< _TBase >::getRight

/*---------------------------------------------------------------------------*/

template class AndRule< IAttributeRule >;

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
