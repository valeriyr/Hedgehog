
#ifndef __SE_EXPORTER_HPP__
#define __SE_EXPORTER_HPP__

/*---------------------------------------------------------------------------*/

#include "script_engine/ih/se_iexporter.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class Exporter
	:	public Tools::Core::BaseWrapper< IExporter >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Exporter( lua_State* _luaEngine, const IEnvironment& _environment );

	virtual ~Exporter();

/*---------------------------------------------------------------------------*/

	/*virtual*/ DataExporter getDataExporter();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	lua_State* m_luaEngine;

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_EXPORTER_HPP__