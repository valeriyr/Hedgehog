
#ifndef __XL_HANDLE_HPP__
#define __XL_HANDLE_HPP__

#include "xml_library/sources/handle/xl_ihandle.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/


template<
		typename _TCallbackFunction
	,	typename _TExtructor1
	,	typename _TExtructor2
	,	typename _TExtructor3
	,	typename _TExtructor4
	>
class Handle
	:	public IHandle
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Handle(
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

class UIntAttributeExtructor
{

public:

	UIntAttributeExtructor( const std::string& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	unsigned int operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName.c_str() ).toUInt();
	}

private:

	const std::string m_attributeName;
};

/*---------------------------------------------------------------------------*/

class BoolAttributeExtructor
{

public:

	BoolAttributeExtructor( const std::string& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	bool operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName.c_str() ).toUInt();
	}

private:

	const std::string m_attributeName;
};

/*---------------------------------------------------------------------------*/

class StringAttributeExtructor
{

public:

	StringAttributeExtructor( const std::string& _attributeName )
		:	m_attributeName( _attributeName )
	{}

	std::string operator () ( const QDomElement& _element )
	{
		return _element.attribute( m_attributeName.c_str() ).toLocal8Bit().data();
	}

private:

	const std::string m_attributeName;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_HANDLE_HPP__