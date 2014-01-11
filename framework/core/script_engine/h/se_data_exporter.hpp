
#ifndef __SE_DATA_EXPORTER_HPP__
#define __SE_DATA_EXPORTER_HPP__

#include <luabind/luabind.hpp>


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

template < typename _TClass, typename _TEnumType >
class EnumExporter
{

public:

	EnumExporter( _TClass& _class, const char* _enumName )
		:	m_enum( _class.enum_( _enumName ) )
	{
	}

	EnumExporter& withItem( const char* _name, const _TEnumType _enum )
	{
		m_enum[ luabind::value( _name, _enum ) ];
		return *this;
	}

private:

	luabind::detail::enum_maker< typename _TClass::self_t > m_enum;
};

/*---------------------------------------------------------------------------*/

template < typename _TClass >
class ClassExporter
{

public:

	ClassExporter( lua_State* _luaEngine, const char* _className )
		:	m_luaEngine( _luaEngine )
		,	m_class( _className )
	{
	}

	~ClassExporter()
	{
		luabind::module( m_luaEngine )
		[
			m_class
		];
	}

	ClassExporter& withConstructor()
	{
		m_class.def( luabind::constructor<>() );
		return *this;
	}

	template< typename _TParamType >
	ClassExporter& withConstructor()
	{
		m_class.def( luabind::constructor< _TParamType >() );
		return *this;
	}

	template< typename _TFirstParamType, typename _TSecondParamType >
	ClassExporter& withConstructor()
	{
		m_class.def( luabind::constructor< _TFirstParamType, _TSecondParamType >() );
		return *this;
	}

	template< typename _TFirstParamType, typename _TSecondParamType, typename _TThirdParamType, typename _TFourthParamType >
	ClassExporter& withConstructor()
	{
		m_class.def( luabind::constructor< _TFirstParamType, _TSecondParamType, _TThirdParamType, _TFourthParamType >() );
		return *this;
	}

	template< typename _TMethod >
	ClassExporter& withMethod( const char* _methodName, _TMethod _method )
	{
		m_class.def( _methodName, _method );
		return *this;
	}

	template< typename _TProperty >
	ClassExporter& withRWProperty( const char* _propertyName, _TProperty _property )
	{
		m_class.def_readwrite( _propertyName, _property );
		return *this;
	}

	template< typename _TEnumType >
	EnumExporter< luabind::class_< _TClass >, _TEnumType > withEnum( const char* _enumName )
	{
		return EnumExporter< luabind::class_< _TClass >, _TEnumType >( m_class, _enumName );
	}

private:

	lua_State* m_luaEngine;
	luabind::class_< _TClass > m_class;
};

/*---------------------------------------------------------------------------*/

template < typename _TClass, typename _TSharedPtr >
class ClassExporterWithShared
{

public:

	ClassExporterWithShared( lua_State* _luaEngine, const char* _className )
		:	m_luaEngine( _luaEngine )
		,	m_class( _className )
	{
	}

	~ClassExporterWithShared()
	{
		luabind::module( m_luaEngine )
		[
			m_class
		];
	}

	ClassExporterWithShared& withConstructor()
	{
		m_class.def( luabind::constructor<>() );
		return *this;
	}

	template< typename _TParamType >
	ClassExporterWithShared& withConstructor()
	{
		m_class.def( luabind::constructor< _TParamType >() );
		return *this;
	}

	template< typename _TFirstParamType, typename _TSecondParamType >
	ClassExporterWithShared& withConstructor()
	{
		m_class.def( luabind::constructor< _TFirstParamType, _TSecondParamType >() );
		return *this;
	}

	template< typename _TFirstParamType, typename _TSecondParamType, typename _TThirdParamType, typename _TFourthParamType >
	ClassExporterWithShared& withConstructor()
	{
		m_class.def( luabind::constructor< _TFirstParamType, _TSecondParamType, _TThirdParamType, _TFourthParamType >() );
		return *this;
	}

	template< typename _TMethod >
	ClassExporterWithShared& withMethod( const char* _methodName, _TMethod _method )
	{
		m_class.def( _methodName, _method );
		return *this;
	}

	template< typename _TProperty >
	ClassExporterWithShared& withRWProperty( const char* _propertyName, _TProperty _property )
	{
		m_class.def_readwrite( _propertyName, _property );
		return *this;
	}

	template< typename _TEnumType >
	EnumExporter< luabind::class_< _TClass, _TSharedPtr >, _TEnumType > withEnum( const char* _enumName )
	{
		return EnumExporter< luabind::class_< _TClass, _TSharedPtr >, _TEnumType >( m_class, _enumName );
	}

private:

	lua_State* m_luaEngine;
	luabind::class_< _TClass, _TSharedPtr > m_class;
};

/*---------------------------------------------------------------------------*/

class DataExporter
{

public:

	DataExporter( lua_State* _luaEngine )
		:	m_luaEngine( _luaEngine )
	{}

	template< typename _TClass >
	boost::shared_ptr< ClassExporter< _TClass > > exportClass( const char* _className )
	{
		return boost::shared_ptr< ClassExporter< _TClass > >( new ClassExporter< _TClass >( m_luaEngine, _className ) );
	}

	template< typename _TClass >
	boost::shared_ptr< ClassExporterWithShared< _TClass, boost::shared_ptr< _TClass > > > exportClassWithShared( const char* _className )
	{
		return boost::shared_ptr< ClassExporterWithShared< _TClass, boost::shared_ptr< _TClass > > >( new ClassExporterWithShared< _TClass, boost::shared_ptr< _TClass > >( m_luaEngine, _className ) );
	}

	template< typename _TFunction >
	void exportFunction( const char* _functionName, _TFunction _function )
	{
		luabind::module( m_luaEngine )
		[
			luabind::def( _functionName, _function )
		];
	}

	template< typename _TVariable >
	void exportVariable( const char* _name, _TVariable _variable )
	{
		luabind::globals( m_luaEngine )[ _name ] = _variable;
	}

private:

	lua_State* m_luaEngine;
};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_DATA_EXPORTER_HPP__
