
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/game_manager/gm_game_manager.hpp"

#include "game_manager/sources/actions_queue/gm_iactions_queue.hpp"
#include "game_manager/sources/environment/gm_ienvironment.hpp"

#include "game_manager/sources/actions/gm_move_items_action.hpp"
#include "game_manager/sources/actions/gm_select_items_action.hpp"

#include "landscape_model/ih/lm_iunit.hpp"

#include "network_manager/ih/nm_iudp_connection.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


GameManager::GameManager(
		const IEnvironment& _environment
	,	boost::intrusive_ptr< IActionsQueue > _actionsQueue
	)
	:	m_environment( _environment )
	,	m_connectionInfo( "127.0.0.1", 1988 )
	,	m_connection( _environment.getConnection( m_connectionInfo ) )
	,	m_actionsQueue( _actionsQueue )
{
	m_connection.addConnectionListener( this );

	m_environment.printMessage( QString( "Socket was opened on: '%1:%2'." ).arg( m_connectionInfo.m_address ).arg( m_connectionInfo.m_port ) );

} // GameManager::GameManager


/*---------------------------------------------------------------------------*/


GameManager::~GameManager()
{
	m_connection.removeConnectionListener( this );
	m_environment.closeConnection( m_connectionInfo );

	m_environment.printMessage( QString( "Socket was closed on: '%1:%2'." ).arg( m_connectionInfo.m_address ).arg( m_connectionInfo.m_port ) );

} // GameManager::~GameManager


/*---------------------------------------------------------------------------*/


void
GameManager::run()
{
	m_environment.startThread( "actionsProcessingLoop" );
	m_environment.pushTask( "actionsProcessingLoop", boost::bind( &GameManager::runActionsProcessing, this ), 100 );

} // GameManager::run


/*---------------------------------------------------------------------------*/


void
GameManager::stop()
{
	m_environment.stopThread( "actionsProcessingLoop" );

} // GameManager::stop


/*---------------------------------------------------------------------------*/


void
GameManager::pushMoveAction( const LandscapeModel::Point& _moveTo )
{
	m_actionsQueue->pushBackAction(
		boost::intrusive_ptr< IAction >( new MoveAction( m_environment, _moveTo ) ) );

} // GameManager::pushMoveAction


/*---------------------------------------------------------------------------*/


void
GameManager::pushSelectAction(
		const LandscapeModel::Point& _from
	,	const LandscapeModel::Point& _to )
{
	m_actionsQueue->pushBackAction(
		boost::intrusive_ptr< IAction >( new SelectAction( m_environment, _from, _to ) ) );

} // GameManager::pushSelectAction


/*---------------------------------------------------------------------------*/


void
GameManager::onDataReceive(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const QByteArray& _data )
{
	m_environment.printMessage( QString( "Received data from '%1:%2': '%3'." ).arg( _fromAddress ).arg( _fromPort ).arg( _data.data() ) );

} // ServerEngine::onDataReceive


/*---------------------------------------------------------------------------*/


void
GameManager::runActionsProcessing()
{
	while( m_actionsQueue->hasActions() )
	{
		boost::intrusive_ptr< IAction > action = m_actionsQueue->popFrontAction();

		action->doAction();

		m_connection.sendDataTo( Framework::Core::NetworkManager::ConnectionInfo( "127.0.0.1", 2013 ), QString( "action was finished: '%1'" ).arg( (int)action.get() ).toUtf8() );
	}

} // GameManager::runActionsProcessing


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
