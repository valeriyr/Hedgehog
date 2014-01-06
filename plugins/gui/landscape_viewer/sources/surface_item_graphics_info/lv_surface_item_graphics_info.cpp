
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/surface_item_graphics_info/lv_surface_item_graphics_info.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


SurfaceItemGraphicsInfo::SurfaceItemGraphicsInfo(
		const Core::LandscapeModel::ISurfaceItem::Id& _id
	,	const QString& _atlasName
	,	const QRect _frameRect
	)
	:	m_id( _id )
	,	m_atlasName( _atlasName )
	,	m_frameRect( _frameRect )
{
} // SurfaceItemGraphicsInfo::SurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


SurfaceItemGraphicsInfo::~SurfaceItemGraphicsInfo()
{
} // SurfaceItemGraphicsInfo::~SurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


const Core::LandscapeModel::ISurfaceItem::Id
SurfaceItemGraphicsInfo::getId() const
{
	return m_id;

} // SurfaceItemGraphicsInfo::getId


/*---------------------------------------------------------------------------*/


const QString&
SurfaceItemGraphicsInfo::getAtlasName() const
{
	return m_atlasName;

} // SurfaceItemGraphicsInfo::getAtlasName


/*---------------------------------------------------------------------------*/


const QRect&
SurfaceItemGraphicsInfo::getFrameRect() const
{
	return m_frameRect;

} // SurfaceItemGraphicsInfo::getFrameRect


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
