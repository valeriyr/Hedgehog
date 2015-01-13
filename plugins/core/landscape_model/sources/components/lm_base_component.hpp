
#ifndef __LM_BASE_COMPONENT_HPP__
#define __LM_BASE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class GameObject;

/*---------------------------------------------------------------------------*/

template < typename _TBaseClass >
class BaseComponent
	:	public Tools::Core::BaseWrapper< _TBaseClass >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BaseComponent( GameObject& _object )
		:	m_object( _object )
	{}

	virtual ~BaseComponent() {}

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	GameObject& m_object;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_BASE_COMPONENT_HPP__
