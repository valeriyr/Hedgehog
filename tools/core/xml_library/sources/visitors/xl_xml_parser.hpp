
#ifndef __XL_XML_PARSER_HPP__
#define __XL_XML_PARSER_HPP__

#include "xml_library/ih/xl_ivisitor.hpp"

#include <QtXml/QDomElement>


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IElement;

/*---------------------------------------------------------------------------*/

class Parser
	:	public IVisitor
{

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	Parser( QDomElement& _domElement );

	virtual ~Parser();

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	static void parse ( const IElement& _element, QIODevice& _ioDevise );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void visit ( const TagElement& _tag );

	/*virtual*/ void visit ( const AttributeElement& _attribute );

	/*virtual*/ void visit ( const AndElement& _andElement );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QDomElement m_domElement;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_XML_PARSER_HPP__
