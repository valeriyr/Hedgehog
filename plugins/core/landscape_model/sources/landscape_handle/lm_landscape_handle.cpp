
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"

#include "landscape_model/sources/landscape_model/lm_ilandscape_model_internal.hpp"


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


boost::intrusive_ptr< ILandscape >
LandscapeHandle::getLandscape() const
{
	return getEditableLandscape();

} // LandscapeHandle::getLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeHandle::getPlayer() const
{
	return getEditablePlayer();

} // LandscapeHandle::getPlayer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditableLandscape >
LandscapeHandle::getEditableLandscape() const
{
	return m_landscapeModel.getCurrentLandscapeInternal();

} // LandscapeHandle::getEditableLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditablePlayer >
LandscapeHandle::getEditablePlayer() const
{
	return m_landscapeModel.getPlayerInternal();

} // LandscapeHandle::getEditablePlayer


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
