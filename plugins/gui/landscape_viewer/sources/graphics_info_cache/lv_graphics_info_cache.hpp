
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

	static const QString ms_anySkinIdentifier;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GraphicsInfoCache();

	virtual ~GraphicsInfoCache();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regSurfaceItemGraphicsInfo(
			const QString& _skinId
		,	const Core::LandscapeModel::ISurfaceItem::IdType& _id
		,	const QString& _atlasName
		,	const QRect _frameRect );

	/*virtual*/ void regObjectGraphicsInfo(
			const QString& _skinId
		,	const QString& _objectName
		,	const QString& _atlasName
		,	const QRect _frameRect );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IObjectGraphicsInfo >
		getObjectGraphicsInfo(
				const QString& _skinId
			,	const QString& _objectName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	SurfaceItemGraphicsInfoCollection& _collection ) const;

	/*virtual*/ void fetchObjectsGraphicsInfos(
			const QString& _skinId
		,	ObjectGraphicsInfoCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct GraphicsInfo
	{
		typedef
			std::map< Core::LandscapeModel::ISurfaceItem::IdType, boost::intrusive_ptr< ISurfaceItemGraphicsInfo > >
			SurfaceItemGraphicsInfoCollection;
		typedef
			SurfaceItemGraphicsInfoCollection::const_iterator
			SurfaceItemGraphicsInfoCollectionIterator;

		typedef
			std::map< QString, boost::intrusive_ptr< IObjectGraphicsInfo > >
			ObjectGraphicsInfoCollection;
		typedef
			ObjectGraphicsInfoCollection::const_iterator
			ObjectGraphicsInfoCollectionIterator;

		SurfaceItemGraphicsInfoCollection m_surfaceItemGraphicsInfos;
		ObjectGraphicsInfoCollection m_objectGraphicsInfo;
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

	GraphicsInfoCollection m_graphicsInfoCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_SURFACE_ITEM_GRAPHICS_INFO_CACHE_HPP__
