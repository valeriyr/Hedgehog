
#ifndef __XL_HANDLE_HPP__
#define __XL_HANDLE_HPP__

#include "xml_library/sources/handle/xl_ihandle.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

template< typename _TCallbackFunction >
class Handle
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle( _TCallbackFunction& _callback )
		:	m_callback( _callback )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void operator () ( const QDomElement& _element )
	{
		m_callback();
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	_TCallbackFunction m_callback;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

template<
		typename _TCallbackFunction
	,	typename _TExtructor1
	>
class Handle1
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle1(
			_TCallbackFunction& _callback
		,	_TExtructor1& _extructor1
		)
		:	m_callback( _callback )
		,	m_extructor1( _extructor1 )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void operator () ( const QDomElement& _element )
	{
		m_callback( m_extructor1( _element ) );
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	_TCallbackFunction m_callback;

	_TExtructor1 m_extructor1;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

template<
		typename _TCallbackFunction
	,	typename _TExtructor1
	,	typename _TExtructor2
	>
class Handle2
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle2(
			_TCallbackFunction& _callback
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		)
		:	m_callback( _callback )
		,	m_extructor1( _extructor1 )
		,	m_extructor2( _extructor2 )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void operator () ( const QDomElement& _element )
	{
		m_callback(
				m_extructor1( _element )
			,	m_extructor2( _element )
			);
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	_TCallbackFunction m_callback;

	_TExtructor1 m_extructor1;
	_TExtructor2 m_extructor2;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

template<
		typename _TCallbackFunction
	,	typename _TExtructor1
	,	typename _TExtructor2
	,	typename _TExtructor3
	>
class Handle3
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle3(
			_TCallbackFunction& _callback
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		,	_TExtructor3& _extructor3
		)
		:	m_callback( _callback )
		,	m_extructor1( _extructor1 )
		,	m_extructor2( _extructor2 )
		,	m_extructor3( _extructor3 )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void operator () ( const QDomElement& _element )
	{
		m_callback(
				m_extructor1( _element )
			,	m_extructor2( _element )
			,	m_extructor3( _element )
			);
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	_TCallbackFunction m_callback;

	_TExtructor1 m_extructor1;
	_TExtructor2 m_extructor2;
	_TExtructor3 m_extructor3;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

template<
		typename _TCallbackFunction
	,	typename _TExtructor1
	,	typename _TExtructor2
	,	typename _TExtructor3
	,	typename _TExtructor4
	>
class Handle4
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle4(
			_TCallbackFunction& _callback
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		,	_TExtructor3& _extructor3
		,	_TExtructor4& _extructor4
		)
		:	m_callback( _callback )
		,	m_extructor1( _extructor1 )
		,	m_extructor2( _extructor2 )
		,	m_extructor3( _extructor3 )
		,	m_extructor4( _extructor4 )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void operator () ( const QDomElement& _element )
	{
		m_callback(
				m_extructor1( _element )
			,	m_extructor2( _element )
			,	m_extructor3( _element )
			,	m_extructor4( _element )
			);
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	_TCallbackFunction m_callback;

	_TExtructor1 m_extructor1;
	_TExtructor2 m_extructor2;
	_TExtructor3 m_extructor3;
	_TExtructor4 m_extructor4;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

template<
		typename _TCallbackFunction
	,	typename _TExtructor1
	,	typename _TExtructor2
	,	typename _TExtructor3
	,	typename _TExtructor4
	,	typename _TExtructor5
	>
class Handle5
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle5(
			_TCallbackFunction& _callback
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		,	_TExtructor3& _extructor3
		,	_TExtructor4& _extructor4
		,	_TExtructor5& _extructor5
		)
		:	m_callback( _callback )
		,	m_extructor1( _extructor1 )
		,	m_extructor2( _extructor2 )
		,	m_extructor3( _extructor3 )
		,	m_extructor4( _extructor4 )
		,	m_extructor5( _extructor5 )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void operator () ( const QDomElement& _element )
	{
		m_callback(
				m_extructor1( _element )
			,	m_extructor2( _element )
			,	m_extructor3( _element )
			,	m_extructor4( _element )
			,	m_extructor5( _element )
			);
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	_TCallbackFunction m_callback;

	_TExtructor1 m_extructor1;
	_TExtructor2 m_extructor2;
	_TExtructor3 m_extructor3;
	_TExtructor4 m_extructor4;
	_TExtructor5 m_extructor5;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

template<
		typename _TCallbackFunction
	,	typename _TExtructor1
	,	typename _TExtructor2
	,	typename _TExtructor3
	,	typename _TExtructor4
	,	typename _TExtructor5
	,	typename _TExtructor6
	>
class Handle6
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle6(
			_TCallbackFunction& _callback
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		,	_TExtructor3& _extructor3
		,	_TExtructor4& _extructor4
		,	_TExtructor5& _extructor5
		,	_TExtructor6& _extructor6
		)
		:	m_callback( _callback )
		,	m_extructor1( _extructor1 )
		,	m_extructor2( _extructor2 )
		,	m_extructor3( _extructor3 )
		,	m_extructor4( _extructor4 )
		,	m_extructor5( _extructor5 )
		,	m_extructor6( _extructor6 )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void operator () ( const QDomElement& _element )
	{
		m_callback(
				m_extructor1( _element )
			,	m_extructor2( _element )
			,	m_extructor3( _element )
			,	m_extructor4( _element )
			,	m_extructor5( _element )
			,	m_extructor6( _element )
			);
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	_TCallbackFunction m_callback;

	_TExtructor1 m_extructor1;
	_TExtructor2 m_extructor2;
	_TExtructor3 m_extructor3;
	_TExtructor4 m_extructor4;
	_TExtructor5 m_extructor5;
	_TExtructor6 m_extructor6;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class UIntAttributeExtructor
{

public:

	UIntAttributeExtructor( const QString& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	quint32 operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName ).toUInt();
	}

private:

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class IntAttributeExtructor
{

public:

	IntAttributeExtructor( const QString& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	int operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName ).toInt();
	}

private:

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class FloatAttributeExtructor
{

public:

	FloatAttributeExtructor( const QString& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	float operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName ).toFloat();
	}

private:

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class BoolAttributeExtructor
{

public:

	BoolAttributeExtructor( const QString& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	bool operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName ).toUInt();
	}

private:

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class StringAttributeExtructor
{

public:

	StringAttributeExtructor( const QString& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	QString operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName );
	}

private:

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class ParentStringAttributeExtructor
{

public:

	ParentStringAttributeExtructor( const QString& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	QString operator () ( const QDomElement& _element )
	{
		return _element.parentNode().toElement().attribute( m_attributeName );
	}

private:

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class ParentIntAttributeExtructor
{

public:

	ParentIntAttributeExtructor( const QString& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	int operator () ( const QDomElement& _element )
	{
		return _element.parentNode().toElement().attribute( m_attributeName ).toInt();
	}

private:

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class ChildTagIntAttributeExtructor
{

public:

	ChildTagIntAttributeExtructor( const QString& _childTagName, const QString& _attributeName )
		:	m_childTagName( _childTagName )
		,	m_attributeName( _attributeName )
	{}

	int operator () ( const QDomElement& _element )
	{
		QDomElement childElement( _element.firstChildElement() );

		while( !childElement.isNull() )
		{
			if ( childElement.nodeName() == m_childTagName )
				return childElement.toElement().attribute( m_attributeName ).toInt();

			childElement = childElement.nextSiblingElement();
		}

		return INT_MAX;
	}

private:

	const QString m_childTagName;

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class ChildTagsStringAttributeExtructor
{

public:

	typedef std::vector< QString > ResultCollection;
	typedef ResultCollection::const_iterator ResultCollectionIterator;

public:

	ChildTagsStringAttributeExtructor( const QString& _childTagName, const QString& _attributeName )
		:	m_childTagName( _childTagName )
		,	m_attributeName( _attributeName )
	{}

	ResultCollection operator () ( const QDomElement& _element )
	{
		ResultCollection result;

		QDomElement childElement( _element.firstChildElement() );

		while( !childElement.isNull() )
		{
			if ( childElement.nodeName() == m_childTagName )
				result.push_back( childElement.toElement().attribute( m_attributeName ) );

			childElement = childElement.nextSiblingElement();
		}

		return result;
	}

private:

	const QString m_childTagName;

	const QString m_attributeName;
};

/*---------------------------------------------------------------------------*/

class CDATAExtructor
{

public:

	QString operator () ( const QDomElement& _element )
	{
		return _element.firstChild().toCDATASection().data();
	}
};


/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_HANDLE_HPP__
