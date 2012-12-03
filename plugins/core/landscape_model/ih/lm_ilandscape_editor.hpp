
#ifndef __LM_ILANDSCAPE_EDITOR_HPP__
#define __LM_ILANDSCAPE_EDITOR_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_LANDSCAPE_EDITOR = 1;

/*---------------------------------------------------------------------------*/

struct ILandscapeEditor
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual IEditableLandscape::Ptr
		createLandscape(
			const unsigned int _width
		,	const unsigned int _height ) const = 0;

	virtual IEditableLandscape::Ptr loadLandscape( const std::string& _filePath ) const = 0;

	virtual void saveLandscape(
			const std::string& _filePath 
		,	ILandscape::Ptr _landscape ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_EDITOR_HPP__
