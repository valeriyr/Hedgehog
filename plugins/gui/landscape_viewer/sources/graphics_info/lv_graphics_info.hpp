
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

	/*virtual*/ void setNobodyObjectColor( const QColor& _color );

	/*virtual*/ const QColor& getNobodyObjectColor()const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setStartPointColor( const Core::LandscapeModel::StartPoint::Id& _startPointId, const QColor& _color );

	/*virtual*/ const QColor& getStartPointColor( const Core::LandscapeModel::StartPoint::Id& _startPointId ) const;

	/*virtual*/ void clearStartPointData();

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

	typedef
		std::map< QString, SurfaceGraphicsInfo >
		SurfaceGraphicsInfoCollection;
	typedef
		SurfaceGraphicsInfoCollection::iterator
		SurfaceGraphicsInfoCollectionIterator;
	typedef
		SurfaceGraphicsInfoCollection::const_iterator
		SurfaceGraphicsInfoCollectionConstIterator;

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< QColor >
		PossiblePlayersColorsCollection;

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Core::LandscapeModel::StartPoint::Id, QColor >
		StartPointsDataCollection;
	typedef
		StartPointsDataCollection::const_iterator
		StartPointsDataCollectionIterator;

/*---------------------------------------------------------------------------*/

	SurfaceGraphicsInfoCollection m_surfaceGraphicsInfoCollection;

	PossiblePlayersColorsCollection m_possiblePlayersColors;

	StartPointsDataCollection m_startPointsData;

	QColor m_nobodyObjectColor;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_GRAPHICS_INFO_HPP__
