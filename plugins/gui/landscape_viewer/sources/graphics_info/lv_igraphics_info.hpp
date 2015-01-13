
#ifndef __LV_IGRAPHICS_INFO_HPP__
#define __LV_IGRAPHICS_INFO_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"

#include "iterators/it_iiterator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemGraphicsInfo;

/*---------------------------------------------------------------------------*/

struct IGraphicsInfo
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

	typedef
		boost::shared_ptr< Tools::Core::IIterator< QColor > >
		PossiblePlayersColorIterator;

/*---------------------------------------------------------------------------*/

	virtual void regSurfaceItemGraphicsInfo(
			const QString& _skinId
		,	const Tools::Core::Generators::IGenerator::IdType& _id
		,	const QString& _atlasName
		,	const QRect _frameRect ) = 0;

	virtual boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Tools::Core::Generators::IGenerator::IdType& _id ) const = 0;

	virtual void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	SurfaceItemGraphicsInfoCollection& _collection ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regPossiblePlayersColor( const QColor& _color ) = 0;

	virtual PossiblePlayersColorIterator getPossiblePlayersColors() const = 0;

	virtual void setNobodyObjectColor( const QColor& _color ) = 0;

	virtual const QColor& getNobodyObjectColor() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void setStartPointColor( const Tools::Core::Generators::IGenerator::IdType& _startPointId, const QColor& _color ) = 0;

	virtual const QColor& getStartPointColor( const Tools::Core::Generators::IGenerator::IdType& _startPointId ) const = 0;

	virtual void clearStartPointData() = 0;

	virtual bool colorIsUsed( const QColor& _color ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IGRAPHICS_INFO_HPP__
