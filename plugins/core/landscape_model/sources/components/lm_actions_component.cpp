
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_actions_component.hpp"

#include "landscape_model/sources/actions/lm_iaction.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ActionsComponent::ActionsComponent( Object& _object, const ActionsComponentStaticData& _staticData )
	:	BaseComponent< IActionsComponent >( _object )
	,	m_staticData( _staticData )
	,	m_actionsCollection()
	,	m_periodicalActionsCollection()
{
} // ActionsComponent::ActionsComponent


/*---------------------------------------------------------------------------*/


ActionsComponent::~ActionsComponent()
{
} // ActionsComponent::~ActionsComponent


/*---------------------------------------------------------------------------*/


const ActionsComponentStaticData&
ActionsComponent::getStaticData() const
{
	return m_staticData;

} // ActionsComponent::getStaticData


/*---------------------------------------------------------------------------*/


void
ActionsComponent::pushAction( boost::intrusive_ptr< IAction > _action )
{
	assert( _action && getStaticData().canDoAction( _action->getType() ) );
	m_actionsCollection.push_back( _action );

} // ActionsComponent::pushAction


/*---------------------------------------------------------------------------*/


void
ActionsComponent::popFrontAction()
{
	m_actionsCollection.pop_front();

} // ActionsComponent::popFrontAction


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IAction >
ActionsComponent::frontAction() const
{
	return
			!m_actionsCollection.empty()
		?	m_actionsCollection.front()
		:	boost::intrusive_ptr< IAction >();

} // ActionsComponent::frontAction


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IAction >
ActionsComponent::getAction( const Actions::Enum _type ) const
{
	ActionsCollectionIterator
			begin = m_actionsCollection.begin()
		,	end = m_actionsCollection.end();

	for( ; begin != end; ++begin )
	{
		if ( ( *begin )->getType() == _type )
			return *begin;
	}

	return boost::intrusive_ptr< IAction >();

} // ActionsComponent::getAction


/*---------------------------------------------------------------------------*/


void
ActionsComponent::pushPeriodicalAction( boost::intrusive_ptr< IAction > _action )
{
	assert( _action && getStaticData().canDoAction( _action->getType() ) );
	m_periodicalActionsCollection.push_back( _action );

} // ActionsComponent::pushPeriodicalAction


/*---------------------------------------------------------------------------*/


bool
ActionsComponent::hasPeriodicalActions() const
{
	return !m_periodicalActionsCollection.empty();

} // ActionsComponent::pushPeriodicalAction


/*---------------------------------------------------------------------------*/


void
ActionsComponent::fetchPeriodicalActions( IActionsComponent::ActionsCollection& _collection ) const
{
	_collection = m_periodicalActionsCollection;

} // ActionsComponent::pushPeriodicalAction


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
