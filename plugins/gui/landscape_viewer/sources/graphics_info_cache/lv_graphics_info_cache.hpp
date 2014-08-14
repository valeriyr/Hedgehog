
#ifndef __LV_GRAPHICS_INFO_CACHE_HPP__
#define __LV_GRAPHICS_INFO_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/graphics_info_cache/lv_igraphics_info_cache.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class GraphicsInfoCache
	:	public Tools::Core::BaseWrapper< IGraphicsInfoCache >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GraphicsInfoCache();

	virtual ~GraphicsInfoCache();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regSurfaceItemGraphicsInfo(
			const QString& _skinId
		,	const Core::LandscapeModel::ISurfaceItem::Id& _id
		,	const QString& _atlasName
		,	const QRect _frameRect );

	/*virtual*/ boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) const;

	/*virtual*/ void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	SurfaceItemGraphicsInfoCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regPossiblePlayersColor( const QColor& _color );

	/*virtual*/ IGraphicsInfoCache::PossiblePlayersColorIterator getPossiblePlayersColors() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct GraphicsInfo
	{
		typedef
			std::map< Core::LandscapeModel::ISurfaceItem::Id, boost::intrusive_ptr< ISurfaceItemGraphicsInfo > >
			SurfaceItemGraphicsInfoCollection;
		typedef
			SurfaceItemGraphicsInfoCollection::const_iterator
			SurfaceItemGraphicsInfoCollectionIterator;

		SurfaceItemGraphicsInfoCollection m_surfaceItemGraphicsInfos;
	};

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, GraphicsInfo >
		GraphicsInfoCollection;
	typedef
		GraphicsInfoCollection::iterator
		GraphicsInfoCollectionIterator;
	typedef
		GraphicsInfoCollection::const_iterator
		GraphicsInfoCollectionConstIterator;

	typedef
		std::vector< QColor >
		PossiblePlayersColorsCollection;

	GraphicsInfoCollection m_graphicsInfoCollection;

	PossiblePlayersColorsCollection m_possiblePlayersColors;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_SURFACE_ITEM_GRAPHICS_INFO_CACHE_HPP__
