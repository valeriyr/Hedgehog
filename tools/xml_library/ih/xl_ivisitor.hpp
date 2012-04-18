
#ifndef __XL_IVISITOR_HPP__
#define __XL_IVISITOR_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class TagElement;
class AttributeElement;
class AndElement;

/*---------------------------------------------------------------------------*/

struct IVisitor
{
	virtual void visit ( const TagElement& _tag ) = 0;

	virtual void visit ( const AttributeElement& _attribute ) = 0;

	virtual void visit ( const AndElement& _andElement ) = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IVISITOR_HPP__
