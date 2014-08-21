
#ifndef __LV_GRAPHICS_INFO_HPP__
#define __LV_GRAPHICS_INFO_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/graphics_info/lv_igraphics_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class GraphicsInfo
	:	public Tools::Core::BaseWrapper< IGraphicsInfo >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GraphicsInfo();

	virtual ~GraphicsInfo();

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

	/*virtual*/ IGraphicsInfo::PossiblePlayersColorIterator getPossiblePlayersColors() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct SurfaceGraphicsInfo
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
		std::map< QString, SurfaceGraphicsInfo >
		SurfaceGraphicsInfoCollection;
	typedef
		SurfaceGraphicsInfoCollection::iterator
		SurfaceGraphicsInfoCollectionIterator;
	typedef
		SurfaceGraphicsInfoCollection::const_iterator
		SurfaceGraphicsInfoCollectionConstIterator;

	typedef
		std::vector< QColor >
		PossiblePlayersColorsCollection;

	SurfaceGraphicsInfoCollection m_surfaceGraphicsInfoCollection;

	PossiblePlayersColorsCollection m_possiblePlayersColors;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_GRAPHICS_INFO_HPP__
