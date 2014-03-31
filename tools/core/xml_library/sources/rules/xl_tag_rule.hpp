
#ifndef __XL_TAG_RULE_HPP__
#define __XL_TAG_RULE_HPP__

#include "xml_library/sources/rules/xl_rule.hpp"

#include "xml_library/sources/handle/xl_handle.hpp"
#include "xml_library/sources/elements/xl_tag_element.hpp"

#include "xml_library/sources/rules/xl_binary_rule.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

class Attribute;

/*---------------------------------------------------------------------------*/

class Tag
	:	public Rule
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Tag( const QString& _name );

	virtual ~Tag();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< IElement > getElement() const;

/*---------------------------------------------------------------------------*/

	Tag& operator [] ( const Rule& _rule );

	Tag& operator [] ( const Attribute& _attribute );

	Tag& operator * ();

	Tag& operator + ();

	BinaryRule operator || ( const Tag& _tag );

/*---------------------------------------------------------------------------*/

	template < typename _TCallbackFunction >
	Tag& handle( _TCallbackFunction _callBack )
	{
		m_tagElement->addHandle(
			boost::shared_ptr< Handle< _TCallbackFunction > >(
				new Handle< _TCallbackFunction >( _callBack ) ) );
		return *this;
	}

	template <
			typename _TCallbackFunction
		,	typename _TExtructor1
		>
	Tag& handle(
			_TCallbackFunction _callBack
		,	_TExtructor1& _extructor1
		)
	{
		typedef
			 Handle1<
					_TCallbackFunction
				,	_TExtructor1
				>
				HandleType;

		m_tagElement->addHandle(
			boost::shared_ptr< HandleType >(
				new HandleType(
						_callBack
					,	_extructor1 ) ) );
		return *this;
	}

	template <
			typename _TCallbackFunction
		,	typename _TExtructor1
		,	typename _TExtructor2
		>
	Tag& handle(
			_TCallbackFunction _callBack
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		)
	{
		typedef
			 Handle2<
					_TCallbackFunction
				,	_TExtructor1
				,	_TExtructor2
				>
				HandleType;

		m_tagElement->addHandle(
			boost::shared_ptr< HandleType >(
				new HandleType(
						_callBack
					,	_extructor1
					,	_extructor2 ) ) );
		return *this;
	}

	template <
			typename _TCallbackFunction
		,	typename _TExtructor1
		,	typename _TExtructor2
		,	typename _TExtructor3
		>
	Tag& handle(
			_TCallbackFunction _callBack
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		,	_TExtructor3& _extructor3
		)
	{
		typedef
			 Handle3<
					_TCallbackFunction
				,	_TExtructor1
				,	_TExtructor2
				,	_TExtructor3
				>
				HandleType;

		m_tagElement->addHandle(
			boost::shared_ptr< HandleType >(
				new HandleType(
						_callBack
					,	_extructor1
					,	_extructor2
					,	_extructor3 ) ) );
		return *this;
	}

	template < typename _TCallbackFunction >
	Tag& postHandle( _TCallbackFunction _callBack )
	{
		m_tagElement->addPostHandle(
			boost::shared_ptr< Handle< _TCallbackFunction > >(
				new Handle< _TCallbackFunction >( _callBack ) ) );
		return *this;
	}

	template <
			typename _TCallbackFunction
		,	typename _TExtructor1
		,	typename _TExtructor2
		,	typename _TExtructor3
		,	typename _TExtructor4
		>
	Tag& postHandle(
			_TCallbackFunction _callBack
		,	_TExtructor1& _extructor1
		,	_TExtructor2& _extructor2
		,	_TExtructor3& _extructor3
		,	_TExtructor4& _extructor4
		)
	{
		typedef
			 Handle4<
					_TCallbackFunction
				,	_TExtructor1
				,	_TExtructor2
				,	_TExtructor3
				,	_TExtructor4
				>
				HandleType;

		m_tagElement->addPostHandle(
			boost::shared_ptr< HandleType >(
				new HandleType(
						_callBack
					,	_extructor1
					,	_extructor2
					,	_extructor3
					,	_extructor4 ) ) );
		return *this;
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< TagElement > m_tagElement;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_TAG_RULE_HPP__
