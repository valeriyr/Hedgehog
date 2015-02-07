
#ifndef __SE_FUNCTION_CALLER_HPP__
#define __SE_FUNCTION_CALLER_HPP__

#include <luabind/luabind.hpp>


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

class FunctionCaller
{

public:

	FunctionCaller( lua_State* _luaEngine )
		:	m_luaEngine( _luaEngine )
	{}

	template< typename _TParameter >
	void callFunction( const QString& _functionName, _TParameter _parameter )
	{
		try
		{
			luabind::call_function< void >( m_luaEngine, _functionName.toLocal8Bit().data(), _parameter );
		}
		catch( luabind::error& )
		{
			std::string error = lua_tostring( m_luaEngine, -1 );
			// TODO: print error message here
		}
	}

private:

	lua_State* m_luaEngine;
};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_FUNCTION_CALLER_HPP__
