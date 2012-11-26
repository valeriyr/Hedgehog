
#ifndef __XL_IHANDLE_HPP__
#define __XL_IHANDLE_HPP__

#include <QtXml/QDomElement>

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IHandle
{
	virtual void operator () ( const QDomElement& _element ) = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IHANDLE_HPP__