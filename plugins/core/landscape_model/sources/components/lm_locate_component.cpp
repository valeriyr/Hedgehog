
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_locate_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LocateComponent::LocateComponent(
		Object& _object
	,	const LocateComponentStaticData& _staticData
	,	const QPoint& _location
	)
	:	BaseComponent< ILocateComponent >( _object )
	,	m_staticData( _staticData )
	,	m_location( _location )
	,	m_direction( Direction::South )
{
} // LocateComponent::LocateComponent


/*---------------------------------------------------------------------------*/


LocateComponent::~LocateComponent()
{
} // LocateComponent::~LocateComponent


/*---------------------------------------------------------------------------*/


const LocateComponentStaticData&
LocateComponent::getStaticData() const
{
	return m_staticData;

} // LocateComponent::getStaticData


/*---------------------------------------------------------------------------*/


const Direction::Enum
LocateComponent::getDirection() const
{
	return m_direction;

} // LocateComponent::getDirection


/*---------------------------------------------------------------------------*/


void
LocateComponent::setDirection( const Direction::Enum _direction )
{
	m_direction = _direction;

} // LocateComponent::setDirection


/*---------------------------------------------------------------------------*/


const QRect
LocateComponent::getRect() const
{
	return QRect( m_location, m_staticData.m_size );

} // LocateComponent::getRect


/*---------------------------------------------------------------------------*/


const QPoint&
LocateComponent::getLocation() const
{
	return m_location;

} // LocateComponent::getLocation


/*---------------------------------------------------------------------------*/


void
LocateComponent::setLocation( const QPoint& _location )
{
	m_location = _location;

} // LocateComponent::setLocation


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
