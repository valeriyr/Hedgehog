
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
std::auto_ptr< IRule >
CopyVisitor< _TRuleType >::getResult()
{
	return m_result;

} // CopyVisitor< _TRuleType >::getResult


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
std::auto_ptr< _TRuleType >
CopyVisitor< _TRuleType >::copy ( const _TRuleType& _rule )
{
	CopyVisitor< _TRuleType > visitor;

	_rule.accept( visitor );

	return
		std::auto_ptr< _TRuleType >(
			static_cast< _TRuleType* >( visitor.getResult().release() )
			);

} // CopyVisitor< _TRuleType >::copy


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
void
CopyVisitor< _TRuleType >::visit ( const Tag& _tag )
{
	m_result.reset( new Tag( _tag.getName() ) );

} // CopyVisitor< _TRuleType >::visit


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
void
CopyVisitor< _TRuleType >::visit ( const Attribute& _attribute )
{
	m_result.reset( new Attribute( _attribute.getName() ) );

} // CopyVisitor< _TRuleType >::visit


/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
void
CopyVisitor< _TRuleType >::visit ( const AndAttribute& _andAttribute )
{
	m_result.reset(
		new AndAttribute(
				_andAttribute.getLeft()
			,	_andAttribute.getRight()
			)
		);

} // CopyVisitor< _TRuleType >::visit


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template class CopyVisitor< IAttributeRule >;
template class CopyVisitor< IRule >;

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
