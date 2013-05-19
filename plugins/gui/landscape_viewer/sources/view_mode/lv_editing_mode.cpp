
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_editing_mode.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


EditingMode::EditingMode( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_editableLandscape()
	,	m_landscapeFilePath()
{
} // EditingMode::EditingMode


/*---------------------------------------------------------------------------*/


EditingMode::~EditingMode()
{
} // EditingMode::~EditingMode


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
EditingMode::getCurrentLandscape() const
{
	return m_editableLandscape;

} // EditingMode::getCurrentLandscape


/*---------------------------------------------------------------------------*/


QString
EditingMode::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // EditingMode::getLandscapeFilePath


/*---------------------------------------------------------------------------*/


bool
EditingMode::isPlayingMode() const
{
	return false;

} // EditingMode::isPlayingMode


/*---------------------------------------------------------------------------*/


bool
EditingMode::isEditingMode() const
{
	return true;

} // EditingMode::isEditingMode


/*---------------------------------------------------------------------------*/


void
EditingMode::openLandscape( const QString& _filePath )
{
	/*m_editableLandscape = m_environment.getLandscapeEditor()->createLandscape( 140, 120 );
	m_editableLandscape = m_environment.getLandscapeEditor()->loadLandscape( m_landscapeFilePath );
	landscapeWasOpened();*/

} // EditingMode::openLandscape


/*---------------------------------------------------------------------------*/


void
EditingMode::closeLandscape()
{
	/*
	m_environment.getDescriptionView()->landscapeWasClosed();
	m_environment.getObjectsView()->landscapeWasClosed();
	m_environment.getEditorView()->landscapeWasClosed();
	m_environment.clearMinimap();
	*/

} // EditingMode::closeLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
