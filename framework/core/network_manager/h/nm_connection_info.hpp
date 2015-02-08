
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
		,	m_port( 0 )
	{}

	ConnectionInfo(
			const QString& _address
		,	const quint32 _port
		)
		:	m_address( _address )
		,	m_port( _port )
	{}

/*---------------------------------------------------------------------------*/

	bool isEmpty() const
	{
		return m_address.isEmpty();
	}

/*---------------------------------------------------------------------------*/

	bool operator < ( const ConnectionInfo& _connectionId ) const
	{
		return m_port < _connectionId.m_port || m_address < _connectionId.m_address;
	}

	bool operator == ( const ConnectionInfo& _connectionId ) const
	{
		return m_port == _connectionId.m_port && m_address == _connectionId.m_address;
	}

	bool operator != ( const ConnectionInfo& _connectionId ) const
	{
		return !( *this == _connectionId );
	}

/*---------------------------------------------------------------------------*/

	QString m_address;

	quint32 m_port;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_CONNECTION_INFO_HPP__
