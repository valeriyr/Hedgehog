
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_base_mode.hpp"

#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


BaseMode::BaseMode( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_viewsMediator( new ViewsMediator() )
	,	m_landscape()
	,	m_landscapeFilePath()
{
} // BaseMode::BaseMode


/*---------------------------------------------------------------------------*/


BaseMode::~BaseMode()
{
} // BaseMode::~BaseMode


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
BaseMode::getCurrentLandscape() const
{
	return m_landscape;

} // BaseMode::getCurrentLandscape


/*---------------------------------------------------------------------------*/


QString
BaseMode::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // BaseMode::getLandscapeFilePath


/*---------------------------------------------------------------------------*/


void
BaseMode::landscapeWasOpened(
		const QString& _filePath
	,	boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape > _landscape )
{
	m_landscapeFilePath = _filePath;
	m_landscape = _landscape;

} // BaseMode::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
BaseMode::landscapeWasClosed()
{
	m_landscape.reset();
	m_landscapeFilePath.clear();

} // BaseMode::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
