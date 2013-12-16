
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions_queue/lm_actions_queue.hpp"

#include "landscape_model/sources/actions/lm_iaction.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ActionsQueue::ActionsQueue()
	:	m_actionsCollection()
	,	m_actionsQueueLocker()
{
} // ActionsQueue::ActionsQueue


/*---------------------------------------------------------------------------*/


ActionsQueue::~ActionsQueue()
{
} // ActionsQueue::~ActionsQueue


/*---------------------------------------------------------------------------*/


void
ActionsQueue::pushAction( boost::intrusive_ptr< IAction > _action )
{
	QMutexLocker locker( &m_actionsQueueLocker );

	m_actionsCollection.push_back( _action );

} // ActionsQueue::pushAction


/*---------------------------------------------------------------------------*/


void
ActionsQueue::processAction( const unsigned int _deltaTime )
{
	QMutexLocker locker( &m_actionsQueueLocker );

	ActionsCollectionIterator begin = m_actionsCollection.begin();

	while ( begin != m_actionsCollection.end() )
	{
		( *begin )->processAction( _deltaTime );

		if ( ( *begin )->hasFinished() )
			begin = m_actionsCollection.erase( begin );
		else
			++begin;
	}

} // ActionsQueue::processAction


/*---------------------------------------------------------------------------*/


void
ActionsQueue::clear()
{
	QMutexLocker locker( &m_actionsQueueLocker );
	m_actionsCollection.clear();

} // ActionsQueue::clear


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
