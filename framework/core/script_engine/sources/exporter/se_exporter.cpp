
#include "script_engine/sources/ph/se_ph.hpp"

#include "script_engine/sources/exporter/se_exporter.hpp"

#include "script_engine/sources/environment/se_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/


Exporter::Exporter( lua_State* _luaEngine, const IEnvironment& _environment )
	:	m_luaEngine( _luaEngine )
	,	m_environment( _environment )
{
} // Exporter::Exporter


/*---------------------------------------------------------------------------*/


Exporter::~Exporter()
{
} // Exporter::~Exporter


/*---------------------------------------------------------------------------*/


DataExporter
Exporter::getDataExporter()
{
	return DataExporter( m_luaEngine );

} // Exporter::getDataExporter


/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
