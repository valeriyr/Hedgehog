
#ifndef __LM_LANDSCAPE_HANDLE_HPP__
#define __LM_LANDSCAPE_HANDLE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_handle.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModelInternal;

/*---------------------------------------------------------------------------*/

class LandscapeHandle
	:	public Tools::Core::BaseWrapper< ILandscapeHandle >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeHandle(
			boost::intrusive_ptr< ILandscape > _landscape
		,	boost::intrusive_ptr< IPlayer > _player
		,	QMutex& _locker );

	virtual ~LandscapeHandle();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< ILandscape > m_landscape;

	boost::intrusive_ptr< IPlayer > m_player;

	QMutexLocker m_lockerHolder;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_HANDLE_HPP__
