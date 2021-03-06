
#ifndef __LM_STAY_ALONE_CHECKER_HPP__
#define __LM_STAY_ALONE_CHECKER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/victory_checker/lm_ivictory_checker.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModel;

/*---------------------------------------------------------------------------*/

class StayAloneChecker
	:	public Tools::Core::BaseWrapper< IVictoryChecker >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	StayAloneChecker( const ILandscapeModel& _landscapeModel );

	virtual ~StayAloneChecker();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool check() const;

	/*virtual*/ const VictoryCondition::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	bool onlyMyOrNeutralObjects(
			const ILandscape::ObjectsCollection& _objects
		,	const Tools::Core::Generators::IGenerator::IdType& _playerId ) const;

/*---------------------------------------------------------------------------*/

	const ILandscapeModel& m_landscapeModel;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_STAY_ALONE_CHECKER_HPP__
