
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_editor/lm_landscape_editor.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeEditor::LandscapeEditor(
		const ILandscapeSerializer& _landscapeSerializer
	,	const ISurfaceItemsCache& _surfaceItemsCache
	)
	:	m_landscapeSerializer( _landscapeSerializer )
	,	m_surfaceItemsCache( _surfaceItemsCache )
{
} // LandscapeEditor::LandscapeEditor


/*---------------------------------------------------------------------------*/


LandscapeEditor::~LandscapeEditor()
{
} // LandscapeEditor::~LandscapeEditor


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditableLandscape >
LandscapeEditor::createLandscape(
		const unsigned int _width
	,	const unsigned int _height ) const
{
	boost::intrusive_ptr< IEditableLandscape > newLandscape( new Landscape( m_surfaceItemsCache ) );

	newLandscape->setSize( _width, _height );

	return newLandscape;

} // LandscapeEditor::createLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditableLandscape >
LandscapeEditor::loadLandscape( const QString& _filePath ) const
{
	boost::intrusive_ptr< IEditableLandscape > newLandscape( new Landscape( m_surfaceItemsCache ) );

	try
	{
		m_landscapeSerializer.load( *newLandscape, _filePath );
	}
	catch( ... )
	{
		return boost::intrusive_ptr< IEditableLandscape >();
	}

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
