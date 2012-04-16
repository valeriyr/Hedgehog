
/** Copy visitor declaration */

#ifndef __XL_COPY_VISITOR_HPP__
#define __XL_COPY_VISITOR_HPP__

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IRule;

/*---------------------------------------------------------------------------*/


template < typename _TRuleType >
class CopyVisitor
	:	public IVisitor
{

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	CopyVisitor();

	virtual ~CopyVisitor();

	std::auto_ptr< _TRuleType > getResult();

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	static std::auto_ptr< _TRuleType > copy ( const _TRuleType& _rule );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void visit ( const Tag& _tag );

	/*virtual*/ void visit ( const Attribute& _attribute );

	/*virtual*/ void visit ( const AndAttributeRule& _andAttributeRule );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	std::auto_ptr< _TRuleType > m_result;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_COPY_VISITOR_HPP__
