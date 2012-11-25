
#ifndef __XL_TAG_ELEMENT_HPP__
#define __XL_TAG_ELEMENT_HPP__

#include "xml_library/ih/xl_itag_element.hpp"
#include "xml_library/sources/elements/xl_base_element.hpp"

#include "xml_library/sources/handle/xl_ihandle.hpp"

#include "iterators/it_simple_iterator.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class TagElement
	:	public BaseElement< ITagElement >
{

/*---------------------------------------------------------------------------*/

	typedef BaseElement< ITagElement > BaseType;

	typedef
		std::vector< boost::shared_ptr< IHandle > >
		HandlesCollectionType;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	typedef
		SimpleIterator< HandlesCollectionType >
		HandlesCollectionIteratorType;

	typedef
		boost::shared_ptr< HandlesCollectionIteratorType >
		HandlesCollectionIteratorTypePtr;

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

	void addHandle( boost::shared_ptr< IHandle > _handle );

	void addPostHandle( boost::shared_ptr< IHandle > _handle );

	HandlesCollectionIteratorTypePtr getHandles() const;

	HandlesCollectionIteratorTypePtr getPostHandles() const;

/*---------------------------------------------------------------------------*/

	void setChildrenRule( boost::shared_ptr< IElement > _rule );

	void setAttributesRule( boost::shared_ptr< IElement > _rule  );

	void setRepeatMode( RepeatMode::Enum _repeatMode  );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	HandlesCollectionType m_handlesCollectionType;

	HandlesCollectionType m_postHandlesCollectionType;

	boost::shared_ptr< IElement > m_childrenRule;

	boost::shared_ptr< IElement > m_attributesRule;

	RepeatMode::Enum m_repetMode;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_TAG_ELEMENT_HPP__
