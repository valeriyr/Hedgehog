
#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/handle/xl_handle.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------


template< typename _TCallbackFunction >
Handle< _TCallbackFunction >::Handle( _TCallbackFunction& _callback )
	:	m_callback( _callback )
{
} // Handle< _TCallbackFunction >::Handle


/*---------------------------------------------------------------------------


template< typename _TCallbackFunction >
void
Handle< _TCallbackFunction >::operator () ( const QDomElement& _element )
{
	_callback();

} // Handle< _TCallbackFunction >::operator ()


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
