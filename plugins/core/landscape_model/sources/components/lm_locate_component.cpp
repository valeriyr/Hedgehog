
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_locate_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LocateComponent::LocateComponent(
		GameObject& _object
	,	const ILocateComponent::StaticData& _staticData
	,	const QPoint& _location
	)
	:	BaseComponent< ILocateComponent >( _object )
	,	m_staticData( _staticData )
	,	m_location( _location )
	,	m_direction( Direction::South )
	,	m_isHidden( false )
{
} // LocateComponent::LocateComponent


/*---------------------------------------------------------------------------*/


LocateComponent::~LocateComponent()
{
} // LocateComponent::~LocateComponent


/*---------------------------------------------------------------------------*/


const ILocateComponent::StaticData&
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


bool
LocateComponent::isHidden() const
{
	return m_isHidden;

} // LocateComponent::isHidden


/*---------------------------------------------------------------------------*/


void
LocateComponent::setHidden( const bool _hidden )
{
	m_isHidden = _hidden;

} // LocateComponent::setHidden


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
