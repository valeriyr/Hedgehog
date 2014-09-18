
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/ai/ai_goals/lm_wait_goal.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


WaitGoal::WaitGoal( const TickType& _ticks )
	:	m_ticks( _ticks )
{
} // WaitGoal::WaitGoal


/*---------------------------------------------------------------------------*/


WaitGoal::~WaitGoal()
{
} // WaitGoal::~WaitGoal


/*---------------------------------------------------------------------------*/


bool
WaitGoal::process()
{
	if ( m_ticks > 0 )
		--m_ticks;

	return m_ticks <= 0;

} // WaitGoal::process


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
