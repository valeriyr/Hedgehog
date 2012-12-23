
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_objects/lm_base_landscape_object.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BaseLandscapeObject::BaseLandscapeObject(
		unsigned int _width
	,	unsigned int _height
	)
	:	m_width( _width )
	,	m_height( _height )
{
} // BaseLandscapeObject::BaseLandscapeObject


/*---------------------------------------------------------------------------*/


BaseLandscapeObject::~BaseLandscapeObject()
{
} // BaseLandscapeObject::~BaseLandscapeObject


/*---------------------------------------------------------------------------*/


unsigned int
BaseLandscapeObject::getWidth() const
{
	return m_width;

} // BaseLandscapeObject::getWidth


/*---------------------------------------------------------------------------*/


unsigned int
BaseLandscapeObject::getHeight() const
{
	return m_height;

} // BaseLandscapeObject::getHeight


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
