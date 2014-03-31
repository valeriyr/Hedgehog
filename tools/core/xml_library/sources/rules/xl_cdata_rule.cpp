
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_cdata_rule.hpp"

#include "xml_library/sources/elements/xl_cdata_element.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


CDATA::CDATA()
	:	Rule()
	,	m_CDATAElement( new CDATAElement() )
{
} // CDATA::CDATA


/*---------------------------------------------------------------------------*/


CDATA::~CDATA()
{
} // CDATA::~CDATA


/*---------------------------------------------------------------------------*/


boost::shared_ptr< IElement >
CDATA::getElement() const
{
	return m_CDATAElement;

} // CDATA::getElement


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/
