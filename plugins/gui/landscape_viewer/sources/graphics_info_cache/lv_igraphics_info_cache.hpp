
#ifndef __LV_IGRAPHICS_INFO_CACHE_HPP__
#define __LV_IGRAPHICS_INFO_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemGraphicsInfo;
struct IObjectGraphicsInfo;

/*---------------------------------------------------------------------------*/

struct IGraphicsInfoCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void regSurfaceItemGraphicsInfo(
			const QString& _skinId
		,	const Core::LandscapeModel::ISurfaceItem::IdType& _id
		,	const QString& _atlasName
		,	const QRect _frameRect ) = 0;

	virtual void regObjectGraphicsInfo(
			const QString& _skinId
		,	const QString& _objectName
		,	const QString& _atlasName
		,	const QRect _frameRect ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const = 0;

	virtual boost::intrusive_ptr< IObjectGraphicsInfo >
		getObjectGraphicsInfo(
				const QString& _skinId
			,	const QString& _objectName ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IGRAPHICS_INFO_CACHE_HPP__
