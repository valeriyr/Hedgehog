
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/elements/xl_binary_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


BinaryElement::BinaryElement(
		boost::shared_ptr< IElement > _left
	,	boost::shared_ptr< IElement > _right
	)
	:	m_left( _left )
	,	m_right( _right )
{
	assert( _left );
	assert( _right );

} // AndElement::AndElement


/*---------------------------------------------------------------------------*/


const IElement&
BinaryElement::getLeft() const
{
	return *m_left;

} // BinaryElement::getLeft


/*---------------------------------------------------------------------------*/


const IElement&
BinaryElement::getRight() const
{
	return *m_right;

} // BinaryElement::getRight


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
