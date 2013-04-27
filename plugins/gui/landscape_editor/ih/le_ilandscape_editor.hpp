
#ifndef __LE_ILANDSCAPE_EDITOR_HPP__
#define __LE_ILANDSCAPE_EDITOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_LANDSCAPE_EDITOR = 0;

/*---------------------------------------------------------------------------*/

struct ILandscapeEditor
	:	public Tools::Core::IBase
{
	virtual void setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight ) = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_ILANDSCAPE_EDITOR_HPP__
