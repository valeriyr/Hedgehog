
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_handle/lm_landscape_handle.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeHandle::LandscapeHandle(
		boost::intrusive_ptr< ILandscape >& _landscape
	,	boost::intrusive_ptr< IPlayer >& _player
	,	QMutex& _mutex
	)
	:	m_lockerHolder( &_mutex )
	,	m_landscape( _landscape )
	,	m_player( _player )
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
	return m_landscape;

} // LandscapeHandle::getLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeHandle::getPlayer() const
{
	return m_player;

} // LandscapeHandle::getPlayer


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
