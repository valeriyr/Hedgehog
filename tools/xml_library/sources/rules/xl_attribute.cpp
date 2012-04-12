
/** XML attribute implementation */

#include "xml_library/sources/ph/xl_ph.hpp"

#include "xml_library/sources/rules/xl_attribute.hpp"

#include "xml_library/ih/xl_ivisitor.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


Attribute::Attribute( const QString& _attributeName )
	:	BaseType( _attributeName )
{
} // Attribute::Attribute


/*---------------------------------------------------------------------------*/


void
Attribute::accept ( IVisitor& _visitor ) const
{
	_visitor.visit( *this );

} // Attribute::accept


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/
