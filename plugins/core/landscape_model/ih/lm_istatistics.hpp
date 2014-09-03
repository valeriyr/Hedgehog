
#ifndef __LM_ISTATISTICS_HPP__
#define __LM_ISTATISTICS_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_STATISTICS = 4;

/*---------------------------------------------------------------------------*/

struct IStatistics
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual int getPlayerObjectsCount( const IPlayer::Id& _id ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISTATISTICS_HPP__
