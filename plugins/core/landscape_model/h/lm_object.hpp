
#ifndef __LM_OBJECT_HPP__
#define __LM_OBJECT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_object_states.hpp"

#include "landscape_model/h/components/lm_component_id.hpp"
#include "landscape_model/ih/components/lm_itrain_component.hpp"
#include "landscape_model/ih/components/lm_ihealth_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_imove_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"
#include "landscape_model/ih/components/lm_igenerate_resources_component.hpp"
#include "landscape_model/ih/components/lm_iattack_component.hpp"
#include "landscape_model/ih/components/lm_ibuild_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Object
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	typedef int UniqueId;
	static const UniqueId ms_wrongId = -1;

/*---------------------------------------------------------------------------*/

	Object( const QString& _name )
		:	m_name( _name )
		,	m_id( ms_wrongId )
		,	m_state( ObjectState::Standing )
	{
		static unsigned int ms_uniqueIdsCounter = 0;
		*const_cast< UniqueId* >( &m_id ) = ++ms_uniqueIdsCounter;
	}

/*---------------------------------------------------------------------------*/

	const QString& getName() const { return m_name; }

	const UniqueId& getUniqueId() const { return m_id; }

	const ObjectState::Enum getState() const { return m_state; }

/*---------------------------------------------------------------------------*/

	void setState( const ObjectState::Enum _state ) { m_state = _state; }

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

	const QString m_name;

	const UniqueId m_id;

	ObjectState::Enum m_state;

	ComponentsCollection m_components;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_OBJECT_HPP__
