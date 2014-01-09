
#ifndef __SE_IEXPORTER_HPP__
#define __SE_IEXPORTER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "script_engine/h/se_data_exporter.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_EXPORTER = 1;

/*---------------------------------------------------------------------------*/

struct IExporter
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual DataExporter getDataExporter() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_IEXPORTER_HPP__
