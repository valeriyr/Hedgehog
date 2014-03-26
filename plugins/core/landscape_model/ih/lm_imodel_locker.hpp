
#ifndef __LM_IMODEL_LOCKER_HPP__
#define __LM_IMODEL_LOCKER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_iplayer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IModelLocker
	:	public Tools::Core::IBase
{
	virtual boost::intrusive_ptr< ILandscape > getLandscape() const = 0;

	virtual boost::intrusive_ptr< IPlayer > getPlayer( const IPlayer::Id& _id ) const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IMODEL_LOCKER_HPP__
