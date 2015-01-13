
#ifndef __EM_EVENT_HPP__
#define __EM_EVENT_HPP__

#include "object/tl_object.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {


/*---------------------------------------------------------------------------*/

const QString EventType = "Type";

/*---------------------------------------------------------------------------*/

class Event
	:	public Tools::Core::Object
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Event( const QString& _type )
	{
		pushMember( EventType, _type );
	}

	template< typename _TMember >
	Event& pushMember( const QString& _name, const _TMember& _value )
	{
		Tools::Core::Object::pushMember( _name, _value );
		return *this;
	}

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_EVENT_HPP__
