
#ifndef __LV_IMAP_PREVIEW_GENERATOR_HPP__
#define __LV_IMAP_PREVIEW_GENERATOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

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
		enum Enum : qint32
		{
				Surface		= 0x00000001
			,	Objects		= 0x00000010
			,	StartPoints	= 0x00000100
		};

		typedef qint32 Mask;
	};

/*---------------------------------------------------------------------------*/

	static const QSize ms_fixedWidgetSize;

/*---------------------------------------------------------------------------*/

	virtual void generate(
			QPixmap& _generateTo
		,	const GenerateLayers::Mask& _mask ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IMAP_PREVIEW_GENERATOR_HPP__
