
#ifndef __SE_DATA_EXPORTER_HPP__
#define __SE_DATA_EXPORTER_HPP__

#include <luabind/luabind.hpp>


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

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

	template< typename _TMethod >
	ClassExporter& withMethod( const char* _methodName, _TMethod _method )
	{
		m_class.def( _methodName, _method );
		return *this;
	}

private:

	lua_State* m_luaEngine;
	luabind::class_< _TClass > m_class;
};

/*---------------------------------------------------------------------------*/

class DataExporter
{

public:

	DataExporter( lua_State* _luaEngine )
		:	m_luaEngine( _luaEngine )
	{}

	template< typename _TClass >
	ClassExporter< _TClass > exportClass( const char* _className )
	{
		return ClassExporter< _TClass >( m_luaEngine, _className );
	}

	template< typename _TFunction >
	void exportFunction( const char* _functionName, _TFunction _function )
	{
		luabind::module( m_luaEngine )
		[
			luabind::def( _functionName, _function )
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

#endif // __SE_DATA_EXPORTER_HPP__
