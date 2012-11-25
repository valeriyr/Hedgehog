
#ifndef __CN_PLUGIN_INSTANCE_HPP__
#define __CN_PLUGIN_INSTANCE_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/sources/connector/cn_iconnector.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsManagerInternal;

/*---------------------------------------------------------------------------*/

class Connector
	:	public Tools::Core::BaseWrapper< IConnector >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Connector();

	virtual ~Connector();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initialize( const std::string& _pluginsDirectory );

	/*virtual*/ void close();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IPluginsManagerInternal > m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGIN_INSTANCE_HPP__
