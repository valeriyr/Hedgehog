
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_manager/lm_landscape_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeManager::LandscapeManager( const ILandscapeSerializer& _landscapeSerializer )
	:	m_landscapeSerializer( _landscapeSerializer )
	,	m_currentLandscape()
{
} // LandscapeManager::LandscapeManager


/*---------------------------------------------------------------------------*/


LandscapeManager::~LandscapeManager()
{
} // LandscapeManager::~LandscapeManager


/*---------------------------------------------------------------------------*/


void
LandscapeManager::initCurrentLandscape ( const QString& _filePath )
{
} // LandscapeManager::initCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeManager::closeCurrentLandscape()
{
	m_currentLandscape.reset();

} // LandscapeManager::closeCurrentLandscape


/*---------------------------------------------------------------------------*/


ILandscape::Ptr
LandscapeManager::getCurrentLandscape() const
{
	return m_currentLandscape;

} // LandscapeManager::getCurrentLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
