
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_base_mode.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


BaseMode::BaseMode( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_editableLandscape()
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
	return m_editableLandscape;

} // BaseMode::getCurrentLandscape


/*---------------------------------------------------------------------------*/


QString
BaseMode::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // BaseMode::getLandscapeFilePath


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
