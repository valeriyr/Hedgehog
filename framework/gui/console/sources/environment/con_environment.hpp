
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

	/*virtual*/ void executeScript( const QString& _script ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool hasInternalCommand( const QString& _command ) const;

	/*virtual*/ void executeInternalCommand( const QString& _command ) const;

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
