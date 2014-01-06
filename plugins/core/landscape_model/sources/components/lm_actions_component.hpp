
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

	ActionsComponent( Object& _object, const ActionsComponentStaticData& _staticData );

	virtual ~ActionsComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const ActionsComponentStaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushAction( boost::intrusive_ptr< IAction > _action );

	/*virtual*/ void popFrontAction();

	/*virtual*/ boost::intrusive_ptr< IAction > frontAction() const;

	/*virtual*/ boost::intrusive_ptr< IAction > getAction( const Actions::Enum _type ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::list< boost::intrusive_ptr< IAction > >
		ActionsCollection;
	typedef
		ActionsCollection::const_iterator
		ActionsCollectionIterator;

/*---------------------------------------------------------------------------*/

	const ActionsComponentStaticData& m_staticData;

	ActionsCollection m_actionsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ACTIONS_COMPONENT_HPP__
