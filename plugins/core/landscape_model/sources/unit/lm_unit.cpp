
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/unit/lm_unit.hpp"

#include "landscape_model/ih/lm_iobject_type.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Unit::Unit(
		boost::intrusive_ptr< IObjectType > _type
	,	const QRect& _possition
	)
	:	m_type( _type )
	,	m_health( m_type->getMaximumHealth() )
	,	m_possition( _possition )
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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
