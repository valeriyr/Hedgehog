
#ifndef __LM_MODEL_LOCKER_HPP__
#define __LM_MODEL_LOCKER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_imodel_locker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class ModelLocker
	:	public Tools::Core::BaseWrapper< IModelLocker >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ModelLocker(
			boost::intrusive_ptr< ILandscape >& _landscape
		,	boost::intrusive_ptr< IPlayer >& _player
		,	QMutex& _mutex );

	virtual ~ModelLocker();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const IPlayer::Id& _id ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QMutexLocker m_lockerHolder;

	boost::intrusive_ptr< ILandscape > m_landscape;

	boost::intrusive_ptr< IPlayer > m_player;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MODEL_LOCKER_HPP__
