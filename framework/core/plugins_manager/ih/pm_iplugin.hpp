
#ifndef __PM_IPLUGIN_HPP__
#define __PM_IPLUGIN_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct IPluginsManager;

/*---------------------------------------------------------------------------*/


struct IPlugin
	:	public Tools::Core::IBase
{
	virtual void initialize( IPluginsManager* _pluginsManager ) = 0;

	virtual void close() = 0;

	virtual boost::intrusive_ptr< Tools::Core::IBase >
		getInterface( const quint32 _interfaceId ) = 0;
};


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_IPLUGIN_HPP__
