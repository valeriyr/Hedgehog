
#ifndef __SE_REGISTER_HPP__
#define __SE_REGISTER_HPP__

#include <luabind/luabind.hpp>


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

template < typename _TClass >
class ClassRegister
{

public:

	ClassRegister( lua_State* _luaEngine, const char* _className )
		:	m_luaEngine( _luaEngine )
		,	m_class( _className )
	{
	}

	~ClassRegister()
	{
		luabind::module( m_luaEngine )
		[
			m_class
		];
	}

	template< typename _TMethod >
	ClassRegister& withMethod( const char* _methodName, _TMethod _method )
	{
		m_class.def( _methodName, _method );
		return *this;
	}

private:

	lua_State* m_luaEngine;
	luabind::class_< _TClass > m_class;
};

/*---------------------------------------------------------------------------*/

class Register
{

public:

	Register( lua_State* _luaEngine )
		:	m_luaEngine( _luaEngine )
	{}

	template< typename _TClass >
	ClassRegister< _TClass > registerClass( const char* _className )
	{
		return ClassRegister< _TClass >( m_luaEngine, _className );
	}

	template< typename _TFunction >
	void registerFunction( const char* _functionName, _TFunction _function )
	{
		luabind::module( m_luaEngine )
		[
			luabind::def( _functionName, _function )
		];
	}

	template< typename _TObject >
	void pushObject( const char* _objectName, _TObject _object )
	{
		luabind::module( m_luaEngine )
		[
			luabind::def( _objectName, _object )
		];
	}

private:

	lua_State* m_luaEngine;
};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_REGISTER_HPP__
