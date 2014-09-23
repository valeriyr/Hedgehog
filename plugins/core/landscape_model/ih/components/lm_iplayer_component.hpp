
#ifndef __LM_IPLAYER_COMPONENT_HPP__
#define __LM_IPLAYER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IPlayerComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual Tools::Core::Generators::IGenerator::IdType getPlayerId() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPLAYER_COMPONENT_HPP__
