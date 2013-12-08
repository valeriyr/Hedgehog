
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeModel::LandscapeModel(
		const ILandscapeSerializer& _landscapeSerializer
	,	const ISurfaceItemsCache& _surfaceItemsCache
	,	const IObjectTypesCache& _objectTypesCache
	)
	:	m_landscapeSerializer( _landscapeSerializer )
	,	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_objectTypesCache( _objectTypesCache )
	,	m_currentLandscape()
	,	m_landscapeLocker()
{
} // LandscapeModel::LandscapeModel


/*---------------------------------------------------------------------------*/


LandscapeModel::~LandscapeModel()
{
} // LandscapeModel::~LandscapeModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initCurrentLandscape ( const QString& _filePath )
{
	boost::intrusive_ptr< IEditableLandscape >
		landscape( new Landscape( m_surfaceItemsCache, m_objectTypesCache ) );

	m_landscapeSerializer.load( *landscape, _filePath );

	m_currentLandscape = landscape;

} // LandscapeModel::initCurrentLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::closeCurrentLandscape()
{
	m_currentLandscape.reset();

} // LandscapeModel::closeCurrentLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscape >
LandscapeModel::getCurrentLandscapeInternal() const
{
	return m_currentLandscape;

} // LandscapeModel::getCurrentLandscapeInternal


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeHandle >
LandscapeModel::getCurrentLandscape()
{
	return boost::intrusive_ptr< ILandscapeHandle >( new LandscapeHandle( *this ) );

} // LandscapeModel::getCurrentLandscape


/*---------------------------------------------------------------------------*/


QMutex&
LandscapeModel::getLandscapeLocker()
{
	return m_landscapeLocker;

} // LandscapeModel::getLandscapeLocker


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
