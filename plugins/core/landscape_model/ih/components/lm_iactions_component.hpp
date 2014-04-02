
#ifndef __LM_IACTIONS_COMPONENT_HPP__
#define __LM_IACTIONS_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_actions.hpp"

#include "iterators/it_iiterator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IAction;

/*---------------------------------------------------------------------------*/

struct IActionsComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct FlushPolicy
	{
		enum Enum
		{
				Force = 0
			,	AsNeeded
		};
	};

/*---------------------------------------------------------------------------*/

	typedef
		boost::shared_ptr< Tools::Core::IIterator< boost::intrusive_ptr< IAction > > >
		ActionsIterator;

/*---------------------------------------------------------------------------*/

	virtual void flushActions( const FlushPolicy::Enum _flushPolicy ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushAction( boost::intrusive_ptr< IAction > _action, bool _flush ) = 0;

	virtual void pushFrontAction( boost::intrusive_ptr< IAction > _action ) = 0;

	virtual void processAction() = 0;

	virtual ActionsIterator getActionsIterator( const Actions::Enum _type ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushPeriodicalAction( boost::intrusive_ptr< IAction > _action ) = 0;

	virtual ActionsIterator getPeriodicalActionsIterator() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IACTIONS_COMPONENT_HPP__
