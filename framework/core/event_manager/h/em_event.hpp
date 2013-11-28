
#ifndef __EM_EVENT_HPP__
#define __EM_EVENT_HPP__


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/

class Event
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Event( const QString& _type )
		:	m_type( _type )
		,	m_attributesCollection()
	{}

	~Event() {}

/*---------------------------------------------------------------------------*/

	const QString& getType() const
	{
		return m_type;
	}

	bool hasAttribute( const QString& _attributeName ) const
	{
		return m_attributesCollection.find( _attributeName ) != m_attributesCollection.end();
	}

	const QVariant& getAttribute( const QString& _attributeName ) const
	{
		assert( hasAttribute( _attributeName ) && "Attribute should be presented!" );
		return m_attributesCollection.find( _attributeName )->second;
	}

/*---------------------------------------------------------------------------*/

	template < typename _TAttributeType >
	void pushAttribute( const QString& _attributeName, const _TAttributeType& _attribute )
	{
		m_attributesCollection[ _attributeName ] = QVariant( _attribute );
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, QVariant >
		AttributesCollection;

/*---------------------------------------------------------------------------*/

	QString m_type;

	AttributesCollection m_attributesCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_EVENT_HPP__
