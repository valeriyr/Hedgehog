
#ifndef __SE_SCRIPTS_EXECUTOR_HPP__
#define __SE_SCRIPTS_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "script_engine/ih/se_iscripts_executor.hpp"

#include "script_engine/h/se_data_exporter.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools
{
	namespace Core
	{
		struct IMessenger;
	}
}

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class ScriptsExecutor
	:	public Tools::Core::BaseWrapper< IScriptsExecutor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ScriptsExecutor( const IEnvironment& _environment );

	virtual ~ScriptsExecutor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void executeFile( const QString& _fileName );

	/*virtual*/ void executeScript( const QString& _script );

/*---------------------------------------------------------------------------*/

	DataExporter getDataExporter();

/*---------------------------------------------------------------------------*/

	static void setExternalMessenger( boost::intrusive_ptr< Tools::Core::IMessenger > _externalMessenger );

	static boost::intrusive_ptr< Tools::Core::IMessenger > getExternalMessenger();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void exportScriptAPI();

	void printErrorMessage();

/*---------------------------------------------------------------------------*/

	lua_State* m_luaEngine;

	const IEnvironment& m_environment;

	static boost::intrusive_ptr< Tools::Core::IMessenger > ms_externalMessenger;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_SCRIPTS_EXECUTOR_HPP__
