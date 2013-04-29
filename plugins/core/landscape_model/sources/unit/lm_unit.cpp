
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/unit/lm_unit.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Unit::Unit(
		const QString& _name
	,	const QString& _bundlePath
	,	const QRect& _rectInBundle )
	:	m_name( _name )
	,	m_bundlePath( _bundlePath )
	,	m_rectInBundle( _rectInBundle )
{
} // Unit::Unit


/*---------------------------------------------------------------------------*/


Unit::Unit( const Unit& _unit )
{
	m_name = _unit.m_name;
	m_bundlePath = _unit.m_bundlePath;
	m_rectInBundle = _unit.m_rectInBundle;

} // Unit::Unit


/*---------------------------------------------------------------------------*/


Unit::~Unit()
{
} // Unit::Unit


/*---------------------------------------------------------------------------*/


const QString&
Unit::getName() const
{
	return m_name;

} // Unit::getName


/*---------------------------------------------------------------------------*/


const QString&
Unit::getBundlePath() const
{
	return m_bundlePath;

} // Unit::getBundlePath


/*---------------------------------------------------------------------------*/


const QRect&
Unit::getRectInBundle() const
{
	return m_rectInBundle;

} // Unit::getRectInBundle


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IUnit >
Unit::clone() const
{
	return boost::intrusive_ptr< IUnit >( new Unit( *this ) );

} // Unit::clone


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
