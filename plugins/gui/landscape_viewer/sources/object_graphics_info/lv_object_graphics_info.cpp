
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/object_graphics_info/lv_object_graphics_info.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


ObjectGraphicsInfo::ObjectGraphicsInfo(
		const QString& _name
	,	const QString& _atlasName
	,	const QRect _frameRect
	)
	:	m_name( _name )
	,	m_atlasName( _atlasName )
	,	m_frameRect( _frameRect )
{
} // ObjectGraphicsInfo::ObjectGraphicsInfo


/*---------------------------------------------------------------------------*/


ObjectGraphicsInfo::~ObjectGraphicsInfo()
{
} // ObjectGraphicsInfo::~ObjectGraphicsInfo


/*---------------------------------------------------------------------------*/


const QString&
ObjectGraphicsInfo::getName() const
{
	return m_name;

} // SurfaceItemGraphicsInfo::getName


/*---------------------------------------------------------------------------*/


const QString&
ObjectGraphicsInfo::getAtlasName() const
{
	return m_atlasName;

} // ObjectGraphicsInfo::getAtlasName


/*---------------------------------------------------------------------------*/


const QRect&
ObjectGraphicsInfo::getFrameRect() const
{
	return m_frameRect;

} // ObjectGraphicsInfo::getFrameRect


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
