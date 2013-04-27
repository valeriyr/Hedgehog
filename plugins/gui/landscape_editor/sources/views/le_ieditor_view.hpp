
#ifndef __LE_IEDITOR_VIEW_HPP__
#define __LE_IEDITOR_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/views/le_ibase_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEditorView
	:	public IBaseView
{

/*---------------------------------------------------------------------------*/

	virtual void setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_IEDITOR_VIEW_HPP__
