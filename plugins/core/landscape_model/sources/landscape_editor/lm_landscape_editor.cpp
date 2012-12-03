
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_editor/lm_landscape_editor.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeEditor::LandscapeEditor()
{
} // LandscapeEditor::LandscapeEditor


/*---------------------------------------------------------------------------*/


LandscapeEditor::~LandscapeEditor()
{
} // LandscapeEditor::~LandscapeEditor


/*---------------------------------------------------------------------------*/


IEditableLandscape::Ptr
LandscapeEditor::createLandscape(
		const unsigned int _width
	,	const unsigned int _height ) const
{
	return IEditableLandscape::Ptr( new Landscape( _width, _height ) );

} // LandscapeEditor::createLandscape


/*---------------------------------------------------------------------------*/


IEditableLandscape::Ptr
LandscapeEditor::loadLandscape( const std::string& _filePath ) const
{
	return IEditableLandscape::Ptr();

} // LandscapeEditor::loadLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::saveLandscape(
		const std::string& _filePath 
	,	ILandscape::Ptr _landscape ) const
{
} // LandscapeEditor::saveLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
