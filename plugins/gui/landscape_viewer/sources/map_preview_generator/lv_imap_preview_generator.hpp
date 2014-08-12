
#ifndef __LV_IMAP_PREVIEW_GENERATOR_HPP__
#define __LV_IMAP_PREVIEW_GENERATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IMapPreviewGenerator
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct GenerateLayers
	{
		enum Enum
		{
				Surface		= 0x00000001
			,	Objects		= 0x00000010
			,	StartPoints	= 0x00000100
		};

		typedef unsigned int Mask;
	};

/*---------------------------------------------------------------------------*/

	static const QSize ms_fixedWidgetSize;

/*---------------------------------------------------------------------------*/

	virtual void generate(
			QPixmap& _generateTo
		,	const Plugins::Core::LandscapeModel::ILandscape& _landscape
		,	const GenerateLayers::Mask& _mask ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IMAP_PREVIEW_GENERATOR_HPP__
