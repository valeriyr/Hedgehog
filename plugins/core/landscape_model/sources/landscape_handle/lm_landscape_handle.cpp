
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"

#include "landscape_model/sources/landscape_model/lm_ilandscape_model_internal.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeHandle::LandscapeHandle( ILandscapeModelInternal& _landscapeModel )
	:	m_landscapeModel( _landscapeModel )
	,	m_lockerHolder( &_landscapeModel.getLandscapeLocker() )
{
} // LandscapeHandle::LandscapeHandle


/*---------------------------------------------------------------------------*/


LandscapeHandle::~LandscapeHandle()
{
} // LandscapeHandle::~LandscapeHandle


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditableLandscape >
LandscapeHandle::getLandscape() const
{
	return m_landscapeModel.getCurrentLandscapeInternal();

} // LandscapeHandle::getLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
