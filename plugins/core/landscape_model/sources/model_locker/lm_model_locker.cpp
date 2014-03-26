
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/model_locker/lm_model_locker.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ModelLocker::ModelLocker(
		boost::intrusive_ptr< ILandscape >& _landscape
	,	boost::intrusive_ptr< IPlayer >& _player
	,	QMutex& _mutex
	)
	:	m_lockerHolder( &_mutex )
	,	m_landscape( _landscape )
	,	m_player( _player )
{
} // ModelLocker::ModelLocker


/*---------------------------------------------------------------------------*/


ModelLocker::~ModelLocker()
{
} // ModelLocker::~ModelLocker


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscape >
ModelLocker::getLandscape() const
{
	return m_landscape;

} // ModelLocker::getLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
ModelLocker::getPlayer( const IPlayer::Id& _id ) const
{
	return m_player;

} // ModelLocker::getPlayer


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
