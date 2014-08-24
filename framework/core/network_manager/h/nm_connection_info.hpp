
#ifndef __NM_CONNECTION_INFO_HPP__
#define __NM_CONNECTION_INFO_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

struct ConnectionInfo
{

/*---------------------------------------------------------------------------*/

	ConnectionInfo()
		:	m_address()
		,	m_port()
	{}

	ConnectionInfo( const QString& _address, const unsigned int _port )
		:	m_address( _address )
		,	m_port( _port )
	{}

/*---------------------------------------------------------------------------*/

	bool operator < ( const ConnectionInfo& _connectionId ) const
	{
		return m_port < _connectionId.m_port || m_address < _connectionId.m_address;
	}

/*---------------------------------------------------------------------------*/

	const QString m_address;

	const unsigned int m_port;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_CONNECTION_INFO_HPP__
