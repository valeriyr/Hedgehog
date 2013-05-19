
#ifndef __CON_ENVIRONMENT_HPP__
#define __CON_ENVIRONMENT_HPP__

#include "console/sources/environment/con_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( const PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void executeCommand( const QString& _commandName ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_ENVIRONMENT_HPP__
