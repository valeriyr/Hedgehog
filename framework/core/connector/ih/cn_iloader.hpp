
#ifndef __CN_ILOADER_HPP__
#define __CN_ILOADER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/h/cn_export.hpp"
#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/


struct InitData
{
	InitData( const std::string& _pluginsDirectory )
		:	m_pluginsDirectory( _pluginsDirectory )
	{}

	const std::string m_pluginsDirectory;
};


/*---------------------------------------------------------------------------*/


struct ILoader
	:	public Tools::Core::IBase
{
	virtual void load( const InitData& _initData ) = 0;

	virtual void unload() = 0;
};


/*---------------------------------------------------------------------------*/

CONNECTOR_EXPORT
		boost::intrusive_ptr< ILoader >
		createLoader();

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_ILOADER_HPP__
