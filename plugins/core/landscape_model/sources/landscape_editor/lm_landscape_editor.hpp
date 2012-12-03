
#ifndef __LM_LANDSCAPE_EDITOR_HPP__
#define __LM_LANDSCAPE_EDITOR_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_editor.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class LandscapeEditor
	:	public Tools::Core::BaseWrapper< ILandscapeEditor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeEditor();

	virtual ~LandscapeEditor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IEditableLandscape >
		createLandscape( const unsigned int _width, const unsigned int _height ) const;

	/*virtual*/ boost::intrusive_ptr< IEditableLandscape >
		loadLandscape( const std::string& _filePath ) const;

	/*virtual*/ void saveLandscape(
			const std::string& _filePath 
		,	boost::intrusive_ptr< ILandscape > _landscape ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_EDITOR_HPP__
