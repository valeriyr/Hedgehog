
#ifndef __ST_ENVIRONMENT_HPP__
#define __ST_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "settings/sources/environment/st_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

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

	/*virtual*/ void riseEvent( const Framework::Core::EventManager::Event& _event ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __ST_ENVIRONMENT_HPP__
