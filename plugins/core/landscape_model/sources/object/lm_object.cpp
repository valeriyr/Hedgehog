
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/object/lm_object.hpp"

#include "landscape_model/ih/lm_iobject_type.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static unsigned int g_objectsCounter = 0;

/*---------------------------------------------------------------------------*/


Object::Object(
		boost::intrusive_ptr< IObjectType > _type
	,	const QPoint& _possition
	)
	:	m_type( _type )
	,	m_health( m_type->getMaximumHealth() )
	,	m_possition( _possition )
	,	m_state( ObjectState::Standing )
	,	m_direction( Direction::Down )
	,	m_id( g_objectsCounter++ )
{
} // Object::Object


/*---------------------------------------------------------------------------*/


Object::~Object()
{
} // Object::Object


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IObjectType >
Object::getType() const
{
	return m_type;

} // Object::getType


/*---------------------------------------------------------------------------*/


const int
Object::getHealth() const
{
	return m_health;

} // Object::getHealth


/*---------------------------------------------------------------------------*/


const QPoint&
Object::getPosition() const
{
	return m_possition;

} // Object::getPosition


/*---------------------------------------------------------------------------*/


const QRect
Object::getRect() const
{
	return QRect( getPosition(), getType()->getSize() );

} // Object::getRect


/*---------------------------------------------------------------------------*/


const IObject::IdType&
Object::getUniqueId() const
{
	return m_id;

} // Object::getUniqueId


/*---------------------------------------------------------------------------*/


const ObjectState::Enum
Object::getState() const
{
	return m_state;

} // Object::getState


/*---------------------------------------------------------------------------*/


const Direction::Enum
Object::getDirection() const
{
	return m_direction;

} // Object::getDirection


/*---------------------------------------------------------------------------*/


void
Object::setPosition( const QPoint& _position )
{
	m_possition = _position;

} // Object::setPosition

/*---------------------------------------------------------------------------*/


void
Object::setState( const ObjectState::Enum _state )
{
	m_state = _state;

} // Object::setState


/*---------------------------------------------------------------------------*/


void
Object::setDirection( const Direction::Enum _direction )
{
	m_direction = _direction;

} // Object::setDirection


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
