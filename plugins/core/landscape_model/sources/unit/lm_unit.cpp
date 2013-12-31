
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/unit/lm_unit.hpp"

#include "landscape_model/ih/lm_iobject_type.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static unsigned int g_unitsCounter = 0;

/*---------------------------------------------------------------------------*/


Unit::Unit(
		boost::intrusive_ptr< IObjectType > _type
	,	const QRect& _possition
	)
	:	m_type( _type )
	,	m_health( m_type->getMaximumHealth() )
	,	m_possition( _possition )
	,	m_state( ObjectState::Standing )
	,	m_direction( Direction::Down )
	,	m_id( g_unitsCounter++ )
{
} // Unit::Unit


/*---------------------------------------------------------------------------*/


Unit::~Unit()
{
} // Unit::Unit


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IObjectType >
Unit::getType() const
{
	return m_type;

} // Unit::getType


/*---------------------------------------------------------------------------*/


const int
Unit::getHealth() const
{
	return m_health;

} // Unit::getHealth


/*---------------------------------------------------------------------------*/


const QRect&
Unit::getPosition() const
{
	return m_possition;

} // Unit::getPosition


/*---------------------------------------------------------------------------*/


const IUnit::IdType&
Unit::getUniqueId() const
{
	return m_id;

} // Unit::getUniqueId


/*---------------------------------------------------------------------------*/


const ObjectState::Enum
Unit::getState() const
{
	return m_state;

} // Unit::getState


/*---------------------------------------------------------------------------*/


const Direction::Enum
Unit::getDirection() const
{
	return m_direction;

} // Unit::getDirection


/*---------------------------------------------------------------------------*/


void
Unit::setPosition( const QRect& _position )
{
	m_possition = _position;

} // Unit::setPosition

/*---------------------------------------------------------------------------*/


void
Unit::setState( const ObjectState::Enum _state )
{
	m_state = _state;

} // Unit::setState


/*---------------------------------------------------------------------------*/


void
Unit::setDirection( const Direction::Enum _direction )
{
	m_direction = _direction;

} // Unit::setDirection


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
