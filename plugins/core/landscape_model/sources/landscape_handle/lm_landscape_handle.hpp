
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
			boost::intrusive_ptr< ILandscape >& _landscape
		,	boost::intrusive_ptr< IPlayer >& _player
		,	QMutex& _mutex );

	virtual ~LandscapeHandle();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer() const;

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

#endif // __LM_LANDSCAPE_HANDLE_HPP__
