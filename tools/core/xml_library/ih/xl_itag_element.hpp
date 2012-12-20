
#ifndef __XL_ITAG_ELEMENT_HPP__
#define __XL_ITAG_ELEMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "xml_library/ih/xl_ielement.hpp"
#include "xml_library/h/xl_repeat_mode.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct ITagElement
	:	public IElement
{
	virtual const QString& getName() const = 0;

	virtual boost::shared_ptr< IElement > getChildrenRule() const = 0;

	virtual boost::shared_ptr< IElement > getAttributesRule() const = 0;

	virtual RepeatMode::Enum getRepeatMode() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_ITAG_ELEMENT_HPP__
