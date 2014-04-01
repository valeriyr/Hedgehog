
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_actions_component.hpp"

#include "landscape_model/ih/lm_iaction.hpp"

#include "iterators/it_simple_iterator.hpp"
#include "iterators/it_filter_iterator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

template< typename _TIteratorType, typename _TReturnType >
struct ActionExtructor
{
	typedef boost::intrusive_ptr< IAction > ReturnType;

	ReturnType extract( const _TIteratorType& _iterator ) const
	{
		return _iterator->m_action;
	}
};

/*---------------------------------------------------------------------------*/

template< typename _TIteratorType >
struct ActionChecker
{
	ActionChecker ( const Actions::Enum _type )
		:	m_type( _type )
	{}

	bool check( const _TIteratorType& _iterator ) const
	{
		return _iterator->m_action->getType() == m_type;
	}

	const Actions::Enum m_type;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ActionsComponent::ActionsComponent( Object& _object )
	:	BaseComponent< IActionsComponent >( _object )
	,	m_actionsCollection()
	,	m_periodicalActionsCollection()
{
} // ActionsComponent::ActionsComponent


/*---------------------------------------------------------------------------*/


ActionsComponent::~ActionsComponent()
{
} // ActionsComponent::~ActionsComponent


/*---------------------------------------------------------------------------*/


void
ActionsComponent::flushActions( const FlushPolicy::Enum _flushPolicy )
{
	ActionsCollectionIterator
			begin = m_actionsCollection.begin()
		,	end = m_actionsCollection.end();

	while ( begin != end )
	{
		if ( ( _flushPolicy == FlushPolicy::Force || begin->m_shouldBeFlushed ) && begin->m_action->cancelProcessing() )
		{
			begin = m_actionsCollection.erase( begin );
		}
		else
		{
			++begin;
		}
	}

} // ActionsComponent::flushActions


/*---------------------------------------------------------------------------*/


void
ActionsComponent::pushAction( boost::intrusive_ptr< IAction > _action, bool _flush )
{
	if ( _flush )
	{
		ActionsCollectionIterator
				begin = m_actionsCollection.begin()
			,	end = m_actionsCollection.end();

		for ( ; begin != end; ++begin )
		{
			begin->m_shouldBeFlushed = true;
		}
	}

	m_actionsCollection.push_back( ActionData( _action ) );

} // ActionsComponent::pushAction


/*---------------------------------------------------------------------------*/


void
ActionsComponent::pushFrontAction( boost::intrusive_ptr< IAction > _action )
{
	m_actionsCollection.push_front( ActionData( _action ) );

} // ActionsComponent::pushFrontAction


/*---------------------------------------------------------------------------*/


void
ActionsComponent::processAction( unsigned int _deltaTime )
{
	flushActions( FlushPolicy::AsNeeded );

	while ( !m_actionsCollection.empty() )
	{
		if ( !m_actionsCollection.front().m_actionInProgress )
		{
			if ( m_actionsCollection.front().m_action->prepareToProcessing() )
			{
				m_actionsCollection.front().m_actionInProgress = true;
			}
			else
			{
				m_actionsCollection.pop_front();
				continue;
			}
		}

		break;
	}

	if ( !m_actionsCollection.empty() )
	{
		boost::intrusive_ptr< IAction > action = m_actionsCollection.front().m_action;

		action->processAction( _deltaTime );

		if ( !action->isInProcessing() )
		{
			removeFinishedAction( action );
		}
	}

} // ActionsComponent::processAction


/*---------------------------------------------------------------------------*/


IActionsComponent::ActionsIterator
ActionsComponent::getActionsIterator( const Actions::Enum _type ) const
{
	return
		IActionsComponent::ActionsIterator(
			new Tools::Core::FilterIterator< ActionsCollection, ActionChecker, ActionExtructor >(
				m_actionsCollection, ActionChecker< ActionsCollectionConstIterator >( _type ) ) );

} // ActionsComponent::getActionsIterator


/*---------------------------------------------------------------------------*/


void
ActionsComponent::pushPeriodicalAction( boost::intrusive_ptr< IAction > _action )
{
	m_periodicalActionsCollection.push_back( _action );

} // ActionsComponent::pushPeriodicalAction


/*---------------------------------------------------------------------------*/


IActionsComponent::ActionsIterator
ActionsComponent::getPeriodicalActionsIterator() const
{
	return
		IActionsComponent::ActionsIterator(
			new Tools::Core::SimpleIterator< ActionsCollection, ActionExtructor >(
				m_periodicalActionsCollection ) );

} // ActionsComponent::getPeriodicalActionsIterator


/*---------------------------------------------------------------------------*/


void
ActionsComponent::removeFinishedAction( boost::intrusive_ptr< IAction > _action )
{
	ActionsCollectionIterator
			begin = m_actionsCollection.begin()
		,	end = m_actionsCollection.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->m_action == _action )
		{
			m_actionsCollection.erase( begin );
			break;
		}
	}

} // ActionsComponent::removeFinishedAction


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
