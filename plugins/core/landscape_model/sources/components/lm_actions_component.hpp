
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

	/*virtual*/ void flushActions( const FlushPolicy::Enum _flushPolicy );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushAction( boost::intrusive_ptr< IAction > _action, bool _flush );

	/*virtual*/ void pushFrontAction( boost::intrusive_ptr< IAction > _action );

	/*virtual*/ void processAction( unsigned int _deltaTime );

	/*virtual*/ IActionsComponent::ActionsIterator getActionsIterator( const Actions::Enum _type ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushPeriodicalAction( boost::intrusive_ptr< IAction > _action );

	/*virtual*/ ActionsIterator getPeriodicalActionsIterator() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void removeFinishedAction( boost::intrusive_ptr< IAction > _action );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct ActionData
	{
		ActionData( boost::intrusive_ptr< IAction > _action )
			:	m_action( _action )
			,	m_shouldBeFlushed( false )
			,	m_actionInProgress( false )
		{}

		boost::intrusive_ptr< IAction > m_action;

		bool m_shouldBeFlushed;
		bool m_actionInProgress;
	};

	typedef
		std::list< ActionData >
		ActionsCollection;
	typedef
		ActionsCollection::iterator
		ActionsCollectionIterator;
	typedef
		ActionsCollection::const_iterator
		ActionsCollectionConstIterator;

/*---------------------------------------------------------------------------*/

	ActionsCollection m_actionsCollection;

	ActionsCollection m_periodicalActionsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ACTIONS_COMPONENT_HPP__
