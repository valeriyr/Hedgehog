
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/visitors/xl_copy_visitor.hpp"

#include "xml_library/sources/rules/xl_attribute.hpp"
#include "xml_library/sources/rules/xl_tag.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
CopyVisitor< _TRuleType >::CopyVisitor()
	:	m_result()
{
} // CopyVisitor< _TRuleType >::CopyVisitor


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
CopyVisitor< _TRuleType >::~CopyVisitor()
{
} // CopyVisitor< _TRuleType >::~CopyVisitor


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
std::auto_ptr< _TRuleType >
CopyVisitor< _TRuleType >::getResult()
{
	return m_result;

} // CopyVisitor< _TRuleType >::getResult


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
std::auto_ptr< _TRuleType >
CopyVisitor< _TRuleType >::copy ( const _TRuleType& _rule )
{
	CopyVisitor visitor;

	_rule.accept( visitor );

	return visitor.getResult();

} // CopyVisitor< _TRuleType >::copy


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
void
CopyVisitor< _TRuleType >::visit ( const Tag& _tag )
{
} // CopyVisitor< _TRuleType >::visit


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
void
CopyVisitor< _TRuleType >::visit ( const Attribute& _attribute )
{
} // CopyVisitor< _TRuleType >::visit


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template class CopyVisitor< IAttributeRule >;

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
