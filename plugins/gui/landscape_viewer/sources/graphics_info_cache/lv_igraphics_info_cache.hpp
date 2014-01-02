
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

/*---------------------------------------------------------------------------*/

struct IGraphicsInfoCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	static const QString ms_anySkinIdentifier;

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< boost::intrusive_ptr< ISurfaceItemGraphicsInfo > >
		SurfaceItemGraphicsInfoCollection;
	typedef
		SurfaceItemGraphicsInfoCollection::iterator
		SurfaceItemGraphicsInfoCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual void regSurfaceItemGraphicsInfo(
			const QString& _skinId
		,	const Core::LandscapeModel::ISurfaceItem::IdType& _id
		,	const QString& _atlasName
		,	const QRect _frameRect ) = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	SurfaceItemGraphicsInfoCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IGRAPHICS_INFO_CACHE_HPP__
