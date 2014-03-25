
#ifndef __LM_IACTIONS_COMPONENT_HPP__
#define __LM_IACTIONS_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_actions.hpp"

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

	typedef
		std::list< boost::intrusive_ptr< IAction > >
		ActionsCollection;
	typedef
		ActionsCollection::const_iterator
		ActionsCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual void pushAction( boost::intrusive_ptr< IAction > _action ) = 0;

	virtual void popFrontAction() = 0;

	virtual boost::intrusive_ptr< IAction > frontAction() const = 0;

	virtual boost::intrusive_ptr< IAction > getAction( const Actions::Enum _type ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushPeriodicalAction( boost::intrusive_ptr< IAction > _action ) = 0;

	virtual bool hasPeriodicalActions() const = 0;

	virtual void fetchPeriodicalActions( ActionsCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IACTIONS_COMPONENT_HPP__
