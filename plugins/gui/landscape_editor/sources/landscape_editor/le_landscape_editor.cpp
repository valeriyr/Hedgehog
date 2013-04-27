
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_editor/le_landscape_editor.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/views/le_ibase_view.hpp"
#include "landscape_editor/sources/views/le_ieditor_view.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeEditor::LandscapeEditor( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_landscapeFilePath()
	,	m_editableLandscape()
{
} // LandscapeEditor::LandscapeEditor


/*---------------------------------------------------------------------------*/


LandscapeEditor::~LandscapeEditor()
{
} // LandscapeEditor::~LandscapeEditor


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::newLandscape()
{
	if ( m_editableLandscape )
		closeLandscape();

	m_landscapeFilePath = "c:/temp/new.hmap";
	m_editableLandscape = m_environment.getLandscapeEditor()->createLandscape( 140, 120 );

	landscapeWasOpened();

} // LandscapeEditor::newLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::openLandscape()
{
	QString landscapeFilePath = m_environment.getDialogsManager()->getOpenFileName( "*.hmap" );

	if ( !landscapeFilePath.isEmpty() )
	{
		if ( m_editableLandscape )
			closeLandscape();

		m_landscapeFilePath = landscapeFilePath;
		m_editableLandscape = m_environment.getLandscapeEditor()->loadLandscape( m_landscapeFilePath );
		landscapeWasOpened();
	}

} // LandscapeEditor::openLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::closeLandscape()
{
	m_landscapeFilePath.clear();
	m_editableLandscape.reset();

	m_environment.getDescriptionView()->landscapeWasClosed();
	m_environment.getObjectsView()->landscapeWasClosed();
	m_environment.getEditorView()->landscapeWasClosed();
	m_environment.clearMinimap();

} // LandscapeEditor::closeLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::saveLandscape()
{
	if ( m_editableLandscape )
		m_environment.getLandscapeEditor()
			->saveLandscape( *m_editableLandscape, m_landscapeFilePath );

} // LandscapeEditor::saveLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::saveAsLandscape()
{
	QString landscapeFilePath = m_environment.getDialogsManager()->getSaveFileName( "*.hmap" );
	m_environment.getLandscapeEditor()
		->saveLandscape( *m_editableLandscape, landscapeFilePath );

} // LandscapeEditor::saveAsLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem >
LandscapeEditor::getSelectedSurfaceItem() const
{
	return m_selectedSurfaceItem ? m_selectedSurfaceItem : m_environment.getDefaultSurfaceItem();

} // LandscapeEditor::getSelectedSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::setSelectedSurfaceItem(
	boost::intrusive_ptr< Core::LandscapeModel::ISurfaceItem > _item )
{
	m_selectedSurfaceItem = _item;

} // LandscapeEditor::setSelectedSurfaceItem


/*---------------------------------------------------------------------------*/


const QString&
LandscapeEditor::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // LandscapeEditor::getLandscapeFilePath


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
LandscapeEditor::getEditableLandscape() const
{
	return m_editableLandscape;

} // LandscapeEditor::getEditableLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight )
{
	m_environment.getEditorView()->setVisibilityRectPosition( _relVisibleWidth, _relVisibleHeight );

} // LandscapeEditor::setVisibilityRectPosition


/*---------------------------------------------------------------------------*/


void
LandscapeEditor::landscapeWasOpened()
{
	m_environment.getDescriptionView()->landscapeWasOpened();
	m_environment.getObjectsView()->landscapeWasOpened();
	m_environment.getEditorView()->landscapeWasOpened();
	m_environment.showLandscapeOnMinimap( *m_editableLandscape );

} // LandscapeEditor::getEditableLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
