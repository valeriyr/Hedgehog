
/** XML visitor interface */

#ifndef __XL_IVISITOR_HPP__
#define __XL_IVISITOR_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class Tag;
class Attribute;

/*---------------------------------------------------------------------------*/

struct IVisitor
{
	virtual void visit ( const Tag& _tag ) = 0;
	virtual void visit ( const Attribute& _attribute ) = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IVISITOR_HPP__
