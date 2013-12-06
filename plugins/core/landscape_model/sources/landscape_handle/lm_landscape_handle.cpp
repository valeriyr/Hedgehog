
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"

#include "landscape_model/sources/landscape_manager/lm_ilandscape_manager_internal.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeHandle::LandscapeHandle( ILandscapeManagerInternal& _landscapeManager )
	:	m_landscapeManager( _landscapeManager )
	,	m_lockerHolder( &_landscapeManager.getLandscapeLocker() )
{
} // LandscapeHandle::LandscapeHandle


/*---------------------------------------------------------------------------*/


LandscapeHandle::~LandscapeHandle()
{
} // LandscapeHandle::~LandscapeHandle


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscape >
LandscapeHandle::getLandscape() const
{
	return m_landscapeManager.getCurrentLandscape();

} // LandscapeHandle::getLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
