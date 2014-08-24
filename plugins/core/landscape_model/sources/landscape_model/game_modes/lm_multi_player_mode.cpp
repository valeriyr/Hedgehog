
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_multi_player_mode.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "network_manager/ih/nm_iudp_connection.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


MultiPlayerMode::MultiPlayerMode(
		ILandscapeModel& _landscapeModel
	,	const IEnvironment& _environment
	,	const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo
	)
	:	m_landscapeModel( _landscapeModel )
	,	m_environment( _environment )
	,	m_connectionInfo( _connectionInfo )
	,	m_connection()
{
	m_connection = m_environment.getConnection( m_connectionInfo );
	m_connection->addConnectionListener( this );

} // MultiPlayerMode::MultiPlayerMode


/*---------------------------------------------------------------------------*/


MultiPlayerMode::~MultiPlayerMode()
{
	m_connection->removeConnectionListener( this );

} // MultiPlayerMode::~MultiPlayerMode


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processCommand()
{
} // MultiPlayerMode::processCommand


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::onDataReceive(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const QByteArray& _data )
{
} // MultiPlayerMode::onDataReceive


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
