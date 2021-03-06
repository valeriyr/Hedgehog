
#ifndef __LM_IPLAYER_HPP__
#define __LM_IPLAYER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_resources_data.hpp"
#include "landscape_model/h/lm_player_type.hpp"
#include "landscape_model/h/lm_priority.hpp"

#include "landscape_model/sources/ai/ai_goals/lm_igoal.hpp"

#include "generators/gn_igenerator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IPlayer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual Tools::Core::Generators::IGenerator::IdType getUniqueId() const = 0;

	virtual PlayerType::Enum getType() const = 0;

	virtual const QString& getRace() const = 0;

	virtual const Tools::Core::Generators::IGenerator::IdType& getStartPointId() const = 0;

	virtual const QString& getName() const = 0;

	virtual const QString& getAIName() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const ResourcesData& getResourcesData() const = 0;

	virtual void substructResources( const ResourcesData& _data ) = 0;

	virtual void addResources( const ResourcesData& _data ) = 0;

	virtual void addResources( const QString& _resourceName, const int _value ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushGoal( const Priority::Enum _priority, const IGoal::Ptr _goal ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IPLAYER_HPP__
