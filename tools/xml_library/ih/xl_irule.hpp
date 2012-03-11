
/** XML rule interface */

#ifndef __XL_IRULE_HPP__
#define __XL_IRULE_HPP__

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IVisitor;

/*---------------------------------------------------------------------------*/

struct IRule
{
	virtual void accept ( IVisitor& _visitor ) const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IRULE_HPP__
