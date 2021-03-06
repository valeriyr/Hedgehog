
#ifndef __XL_IVISITOR_HPP__
#define __XL_IVISITOR_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class TagElement;
class AttributeElement;
class CDATAElement;
class AndElement;
class OrElement;

/*---------------------------------------------------------------------------*/

struct IVisitor
{
	virtual void visit ( const TagElement& _tag ) = 0;

	virtual void visit ( const AttributeElement& _attribute ) = 0;

	virtual void visit ( const CDATAElement& _cdataElement ) = 0;

	virtual void visit ( const AndElement& _andElement ) = 0;

	virtual void visit ( const OrElement& _andElement ) = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IVISITOR_HPP__
