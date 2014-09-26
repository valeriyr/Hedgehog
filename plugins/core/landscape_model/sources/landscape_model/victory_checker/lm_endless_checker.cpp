
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/victory_checker/lm_endless_checker.hpp"

#include "landscape_model/ih/lm_imodel_locker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


EndlessChecker::EndlessChecker( const ILandscapeModel& _landscapeModel )
	:	m_landscapeModel( _landscapeModel )
{
} // EndlessChecker::EndlessChecker


/*---------------------------------------------------------------------------*/


EndlessChecker::~EndlessChecker()
{
} // EndlessChecker::~EndlessChecker


/*---------------------------------------------------------------------------*/


bool
EndlessChecker::check() const
{
	if (	m_landscapeModel.getGameModeType() == IGameMode::Type::Replay
		&&	!m_landscapeModel.hasMoreCommands() )
	{
		return true;
	}

	return false;

} // EndlessChecker::check


/*---------------------------------------------------------------------------*/


const VictoryCondition::Enum
EndlessChecker::getType() const
{
	return VictoryCondition::Endless;

} // EndlessChecker::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
