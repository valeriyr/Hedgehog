
#ifndef __SE_ENVIRONMENT_HPP__
#define __SE_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "script_engine/sources/environment/se_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Tools::Core::IMessenger > getSystemMessenger() const;

	/*virtual*/ const QString& getSystemConfigDirectory() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __SE_ENVIRONMENT_HPP__
