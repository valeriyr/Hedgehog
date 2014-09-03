
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/statistics/lm_statistics.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Statistics::Statistics( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // Statistics::Statistics


/*---------------------------------------------------------------------------*/


Statistics::~Statistics()
{
} // Statistics::~Statistics


/*---------------------------------------------------------------------------*/


int
Statistics::getPlayerObjectsCount( const IPlayer::Id& _id ) const
{
	return 0;

} // Statistics::getPlayerObjectsCount


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
