
#ifndef __LV_MAP_PREVIEW_GENERATOR_HPP__
#define __LV_MAP_PREVIEW_GENERATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/map_preview_generator/lv_imap_preview_generator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
			struct ILandscapeModel;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class MapPreviewGenerator
	:	public Tools::Core::BaseWrapper< IMapPreviewGenerator >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MapPreviewGenerator( const IEnvironment& _environment );

	virtual ~MapPreviewGenerator();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void generate(
			QPixmap& _generateTo
		,	const GenerateLayers::Mask& _mask ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void generateSurface(
			QPixmap& _generateTo
		,	const Plugins::Core::LandscapeModel::ILandscape& _landscape ) const;

	void generateStartPoints(
			QPixmap& _generateTo
		,	const Plugins::Core::LandscapeModel::ILandscape& _landscape ) const;

	void generateObjects(
			QPixmap& _generateTo
		,	const Plugins::Core::LandscapeModel::ILandscapeModel& _landscapeModel ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_MAP_PREVIEW_GENERATOR_HPP__
