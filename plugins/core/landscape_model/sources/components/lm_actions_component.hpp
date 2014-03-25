
#ifndef __LM_ACTIONS_COMPONENT_HPP__
#define __LM_ACTIONS_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_iactions_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class ActionsComponent
	:	public BaseComponent< IActionsComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ActionsComponent( Object& _object );

	virtual ~ActionsComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushAction( boost::intrusive_ptr< IAction > _action );

	/*virtual*/ void popFrontAction();

	/*virtual*/ boost::intrusive_ptr< IAction > frontAction() const;

	/*virtual*/ boost::intrusive_ptr< IAction > getAction( const Actions::Enum _type ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushPeriodicalAction( boost::intrusive_ptr< IAction > _action );

	/*virtual*/ bool hasPeriodicalActions() const;

	/*virtual*/ void fetchPeriodicalActions( IActionsComponent::ActionsCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IActionsComponent::ActionsCollection m_actionsCollection;

	IActionsComponent::ActionsCollection m_periodicalActionsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ACTIONS_COMPONENT_HPP__
