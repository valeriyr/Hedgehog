
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/surface_item/lm_surface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SurfaceItem::SurfaceItem(
		const unsigned int _index
	,	const QString& _bundlePath
	,	const QRect& _rectInBundle
	)
	:	m_index( _index )
	,	m_bundlePath( _bundlePath )
	,	m_rectInBundle( _rectInBundle )
{
} // SurfaceItem::SurfaceItem


/*---------------------------------------------------------------------------*/


SurfaceItem::~SurfaceItem()
{
} // SurfaceItem::~SurfaceItem


/*---------------------------------------------------------------------------*/


unsigned int
SurfaceItem::getIndex() const
{
	return m_index;

} // SurfaceItem::getIndex


/*---------------------------------------------------------------------------*/


const QString&
SurfaceItem::getBundlePath() const
{
	return m_bundlePath;

} // SurfaceItem::getBundlePath


/*---------------------------------------------------------------------------*/


const QRect&
SurfaceItem::getRectInBundle() const
{
	return m_rectInBundle;

} // SurfaceItem::getRectInBundle


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
