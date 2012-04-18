
#ifndef __XL_TAG_ELEMENT_HPP__
#define __XL_TAG_ELEMENT_HPP__

#include "xml_library/ih/xl_itag_element.hpp"
#include "xml_library/sources/elements/xl_base_element.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class TagElement
	:	public BaseElement< ITagElement >
{

/*---------------------------------------------------------------------------*/

	typedef BaseElement< ITagElement > BaseType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	TagElement( const std::string& _tagName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void accept ( IVisitor& _visitor ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< IElement > getChildrenRule() const;

	/*virtual*/ boost::shared_ptr< IElement > getAttributesRule() const;

	/*virtual*/ RepeatMode::Enum getRepeatMode() const;

/*---------------------------------------------------------------------------*/

	void setChildrenRule( boost::shared_ptr< IElement > _rule );

	void setAttributesRule( boost::shared_ptr< IElement > _rule  );

	void setRepeatMode( RepeatMode::Enum _repeatMode  );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< IElement > m_childrenRule;

	boost::shared_ptr< IElement > m_attributesRule;

	RepeatMode::Enum m_repetMode;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_TAG_ELEMENT_HPP__
