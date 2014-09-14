
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_single_player_mode.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static const TickType gs_tickLatency = 1;

/*---------------------------------------------------------------------------*/


SinglePlayerMode::SinglePlayerMode( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_commandsQueue()
{
} // SinglePlayerMode::SinglePlayerMode


/*---------------------------------------------------------------------------*/


SinglePlayerMode::~SinglePlayerMode()
{
} // SinglePlayerMode::~SinglePlayerMode


/*---------------------------------------------------------------------------*/


void
SinglePlayerMode::processCommand( Command& _command )
{
	if ( !CommandId::simulationTimeCommand( _command.m_id ) )
	{
		m_environment.lockModel()->getLandscapeModel()->processCommand( _command );
		return;
	}

	_command.m_targetTick = _command.m_targetTick + gs_tickLatency;

	m_commandsQueue.pushCommand( _command );

} // SinglePlayerMode::processCommand


/*---------------------------------------------------------------------------*/


bool
SinglePlayerMode::prepareToTick( const TickType& _tick )
{
	CommandsQueue::CommandsByTimeCollection commandsForExecution;
	m_commandsQueue.fetchCommandsByTime( _tick, commandsForExecution );

	CommandsQueue::CommandsByTimeCollectionIterator
			commandsForExecutionBegin = commandsForExecution.begin()
		,	commandsForExecutionEnd = commandsForExecution.end();

	boost::intrusive_ptr< IModelLocker > modelLocker = m_environment.lockModel();
	boost::intrusive_ptr< ILandscapeModel > model = modelLocker->getLandscapeModel();

	for ( ; commandsForExecutionBegin != commandsForExecutionEnd; ++commandsForExecutionBegin )
		model->processCommand( commandsForExecutionBegin->second );

	return true;

} // SinglePlayerMode::prepareToTick


/*---------------------------------------------------------------------------*/


const CommandsQueue&
SinglePlayerMode::getCommands() const
{
	return m_commandsQueue;

} // SinglePlayerMode::getCommands


/*---------------------------------------------------------------------------*/


IGameMode::Type::Enum
SinglePlayerMode::getType() const
{
	return IGameMode::Type::SinglePlayer;

} // SinglePlayerMode::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
