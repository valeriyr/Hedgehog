
#ifndef __LM_ACTIONS_COMPONENT_STATIC_DATA_HPP__
#define __LM_ACTIONS_COMPONENT_STATIC_DATA_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_actions.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


struct ActionsComponentStaticData
{
	typedef
		std::set< Actions::Enum >
		ActionsCollection;
	typedef
		ActionsCollection::const_iterator
		ActionsCollectionIterator;

	ActionsComponentStaticData( const ActionsCollection& _possibleActions )
		:	m_possibleActions( _possibleActions )
	{}

	bool canDoAction( const Actions::Enum _action ) const { return m_possibleActions.find( _action ) != m_possibleActions.end(); }

	const ActionsCollection m_possibleActions;
};


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ACTIONS_COMPONENT_STATIC_DATA_HPP__
