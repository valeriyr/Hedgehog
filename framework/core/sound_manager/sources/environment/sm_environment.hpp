
#ifndef __EM_ENVIRONMENT_HPP__
#define __EM_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "sound_manager/sources/environment/sm_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace SoundManager {

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

	/*virtual*/ const QString& getResourcesDirectory() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool getBool( const QString& _key ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_ENVIRONMENT_HPP__
