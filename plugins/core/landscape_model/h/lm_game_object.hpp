
#ifndef __LM_GAME_OBJECT_HPP__
#define __LM_GAME_OBJECT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"

#include "landscape_model/h/lm_object_states.hpp"

#include "landscape_model/h/lm_component_id.hpp"
#include "landscape_model/h/lm_components.hpp"
#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "generators/gn_igenerator.hpp"

#include "object/tl_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

const QString ObjectNameKey = "Name";
const QString ObjectUniqueIdKey = "Id";
const QString ObjectStateKey = "State";

/*---------------------------------------------------------------------------*/

class GameObject
	:	public Tools::Core::Object
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GameObject( const QString& _name, const Tools::Core::Generators::IGenerator::IdType _id )
	{
		pushMember( ObjectNameKey, _name );
		pushMember( ObjectUniqueIdKey, _id );
		pushMember( ObjectStateKey, ObjectState::Standing );
	}

/*---------------------------------------------------------------------------*/

	template< typename _TComponent >
	boost::intrusive_ptr< _TComponent > getComponent( const ComponentId::Enum& _componentId ) const
	{
		ComponentsCollectionIterator iterator = m_components.find( _componentId );

		if ( iterator == m_components.end() )
			return boost::intrusive_ptr< _TComponent >();

		boost::intrusive_ptr< _TComponent > component( dynamic_cast< _TComponent* >( iterator->second.get() ) );

		assert( component );

		return component;
	}

	void addComponent( const ComponentId::Enum& _componentId, boost::intrusive_ptr< IComponent > _component )
	{
		assert( m_components.find( _componentId ) == m_components.end() );
		m_components.insert( std::make_pair( _componentId, _component ) );
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< ComponentId::Enum, boost::intrusive_ptr< IComponent > >
		ComponentsCollection;
	typedef
		ComponentsCollection::const_iterator
		ComponentsCollectionIterator;

/*---------------------------------------------------------------------------*/

	ComponentsCollection m_components;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_GAME_OBJECT_HPP__
