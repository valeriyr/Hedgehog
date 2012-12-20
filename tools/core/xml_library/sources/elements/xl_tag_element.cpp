
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_tag_element.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


TagElement::TagElement( const QString& _tagName )
	:	BaseType( _tagName )
	,	m_handlesCollectionType()
	,	m_postHandlesCollectionType()
	,	m_childrenRule()
	,	m_attributesRule()
	,	m_repetMode( RepeatMode::Once )
{
} // TagElement::TagElement


/*---------------------------------------------------------------------------*/


void
TagElement::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // TagElement::accept


/*---------------------------------------------------------------------------*/


boost::shared_ptr< IElement >
TagElement::getChildrenRule() const
{
	return m_childrenRule;

} // TagElement::getChildrenRule


/*---------------------------------------------------------------------------*/


boost::shared_ptr< IElement >
TagElement::getAttributesRule() const
{
	return m_attributesRule;

} // TagElement:: getAttributesRule


/*---------------------------------------------------------------------------*/


RepeatMode::Enum
TagElement::getRepeatMode() const
{
	return m_repetMode;

} // TagElement::getRepeatMode


/*---------------------------------------------------------------------------*/


void
TagElement::addHandle( boost::shared_ptr< IHandle > _handle )
{
	m_handlesCollectionType.push_back( _handle );

} // TagElement::addHandle


/*---------------------------------------------------------------------------*/


void
TagElement::addPostHandle( boost::shared_ptr< IHandle > _handle )
{
	m_postHandlesCollectionType.push_back( _handle );

} // TagElement::addPostHandle


/*---------------------------------------------------------------------------*/


TagElement::HandlesCollectionIteratorTypePtr
TagElement::getHandles() const
{
	return
		HandlesCollectionIteratorTypePtr(
			new HandlesCollectionIteratorType( m_handlesCollectionType )
			);

} // TagElement::getHandles


/*---------------------------------------------------------------------------*/


TagElement::HandlesCollectionIteratorTypePtr
TagElement::getPostHandles() const
{
	return
		HandlesCollectionIteratorTypePtr(
			new HandlesCollectionIteratorType( m_postHandlesCollectionType )
			);

} // TagElement::getPostHandles


/*---------------------------------------------------------------------------*/


void
TagElement::setChildrenRule( boost::shared_ptr< IElement > _rule )
{
	m_childrenRule = _rule;

} // TagElement::setChildrenRule


/*---------------------------------------------------------------------------*/


void
TagElement::setAttributesRule( boost::shared_ptr< IElement > _rule  )
{
	m_attributesRule = _rule;

} // TagElement::setAttributesRule


/*---------------------------------------------------------------------------*/


void
TagElement::setRepeatMode( RepeatMode::Enum _repeatMode  )
{
	m_repetMode = _repeatMode;

} // TagElement::setRepeatMode


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
