
#ifndef __LM_IUNIT_HPP__
#define __LM_IUNIT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_directions.hpp"
#include "landscape_model/h/lm_object_states.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IObjectType;

/*---------------------------------------------------------------------------*/

struct IUnit
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef int IdType;
	static const IdType ms_wrongId = -1;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IObjectType > getType() const = 0;

	virtual const int getHealth() const = 0;

	virtual const QRect& getPosition() const = 0;

	virtual const IdType& getUniqueId() const = 0;

	virtual const ObjectState::Enum getState() const = 0;

	virtual const Direction::Enum getDirection() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void setPosition( const QRect& _position ) = 0;

	virtual void setState( const ObjectState::Enum _state ) = 0;

	virtual void setDirection( const Direction::Enum _direction ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
