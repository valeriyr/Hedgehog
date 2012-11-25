
#ifndef __XL_XML_FORMAT_CHECKER_HPP__
#define __XL_XML_FORMAT_CHECKER_HPP__

#include "xml_library/ih/xl_ivisitor.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IElement;

/*---------------------------------------------------------------------------*/

class FormatChecker
	:	public IVisitor
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	FormatChecker();

	virtual ~FormatChecker();

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	bool check ( const IElement& _element, QIODevice& _ioDevise );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void visit ( const TagElement& _tag );

	/*virtual*/ void visit ( const AttributeElement& _attribute );

	/*virtual*/ void visit ( const AndElement& _andElement );

/*---------------------------------------------------------------------------*/

	const QString& getXmlSchemaDocument() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QString m_xmlSchemaDocument;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_XML_FORMAT_CHECKER_HPP__
