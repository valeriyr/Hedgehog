
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/victory_checker/lm_stay_alone_checker.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/ih/components/lm_iplayer_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


StayAloneChecker::StayAloneChecker( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // StayAloneChecker::StayAloneChecker


/*---------------------------------------------------------------------------*/


StayAloneChecker::~StayAloneChecker()
{
} // StayAloneChecker::~StayAloneChecker


/*---------------------------------------------------------------------------*/


bool
StayAloneChecker::check() const
{
	boost::intrusive_ptr< IModelLocker > locker = m_environment.lockModel();
	boost::intrusive_ptr< ILandscape > landscape = locker->getLandscapeModel()->getLandscape();

	ILandscape::ObjectsCollection objects;
	landscape->fetchObjects( objects );

	boost::intrusive_ptr< IPlayer > myPlayer = locker->getLandscapeModel()->getMyPlayer();

	ILandscape::ObjectsCollectionIterator
			begin = objects.begin()
		,	end = objects.end();

	for ( ; begin != end; ++begin )
	{
		boost::intrusive_ptr< IPlayerComponent > playerComponent
			= ( *begin )->getComponent< IPlayerComponent >( ComponentId::Player );

		if (	playerComponent
			&&	playerComponent->getPlayerId() != IPlayer::ms_wrondId
			&&	playerComponent->getPlayerId() != myPlayer->getUniqueId()
			&&	( *begin )->getState() != ObjectState::Dying )
		{
			return false;
		}
	}

	return true;

} // StayAloneChecker::check


/*---------------------------------------------------------------------------*/


const VictoryCondition::Enum
StayAloneChecker::getType() const
{
	return VictoryCondition::StayAlone;

} // StayAloneChecker::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
