
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_editor/lm_landscape_editor.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeEditor::LandscapeEditor( const ILandscapeSerializer& _landscapeSerializer )
	:	m_landscapeSerializer( _landscapeSerializer )
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
	IEditableLandscape::Ptr newLandscape( new Landscape() );

	newLandscape->setSize( _width, _height );

	return newLandscape;

} // LandscapeEditor::createLandscape


/*---------------------------------------------------------------------------*/


IEditableLandscape::Ptr
LandscapeEditor::loadLandscape( const QString& _filePath ) const
{
	IEditableLandscape::Ptr newLandscape( new Landscape() );

	m_landscapeSerializer.load( *newLandscape, _filePath );

	return newLandscape;

} // LandscapeEditor::loadLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::saveLandscape(
		const ILandscape& _landscape
	,	const QString& _filePath ) const
{
	m_landscapeSerializer.save( _landscape, _filePath );

} // LandscapeEditor::saveLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
