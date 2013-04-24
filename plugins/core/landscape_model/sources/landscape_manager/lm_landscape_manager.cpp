
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_manager/lm_landscape_manager.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeManager::LandscapeManager(
		const ILandscapeSerializer& _landscapeSerializer
	,	const ISurfaceItemsCache& _surfaceItemsCache
	)
	:	m_landscapeSerializer( _landscapeSerializer )
	,	m_surfaceItemsCache( _surfaceItemsCache )
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
	boost::intrusive_ptr< IEditableLandscape > landscape( new Landscape( m_surfaceItemsCache ) );

	m_landscapeSerializer.load( *landscape, _filePath );

	m_currentLandscape = landscape;

} // LandscapeManager::initCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeManager::closeCurrentLandscape()
{
	m_currentLandscape.reset();

} // LandscapeManager::closeCurrentLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscape >
LandscapeManager::getCurrentLandscape() const
{
	return m_currentLandscape;

} // LandscapeManager::getCurrentLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
