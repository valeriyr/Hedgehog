
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/victory_checker/lm_stay_alone_checker.hpp"

#include "landscape_model/ih/lm_imodel_locker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


StayAloneChecker::StayAloneChecker( const ILandscapeModel& _landscapeModel )
	:	m_landscapeModel( _landscapeModel )
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
	if (	m_landscapeModel.getGameModeType() == IGameMode::Type::Replay
		&&	!m_landscapeModel.hasMoreCommands() )
	{
		return true;
	}

	boost::intrusive_ptr< IPlayer > myPlayer = m_landscapeModel.getMyPlayer();

	if ( !myPlayer )
		return false;

	ILandscape::ObjectsCollection workers;
	m_landscapeModel.fetchWorkers( workers );

	if ( !onlyMyOrNeutralObjects( workers, myPlayer->getUniqueId() ) )
		return false;

	ILandscape::ObjectsCollection objects;
	m_landscapeModel.getLandscape()->fetchObjects( objects );

	return onlyMyOrNeutralObjects( objects, myPlayer->getUniqueId() );

} // StayAloneChecker::check


/*---------------------------------------------------------------------------*/


const VictoryCondition::Enum
StayAloneChecker::getType() const
{
	return VictoryCondition::StayAlone;

} // StayAloneChecker::getType


/*---------------------------------------------------------------------------*/


bool
StayAloneChecker::onlyMyOrNeutralObjects(
		const ILandscape::ObjectsCollection& _objects
	,	const Tools::Core::Generators::IGenerator::IdType& _playerId ) const
{
	ILandscape::ObjectsCollectionIterator
			beginWorkers = _objects.begin()
		,	endWorkers = _objects.end();

	for ( ; beginWorkers != endWorkers; ++beginWorkers )
	{
		Tools::Core::Object::Ptr playerComponent = ( *beginWorkers )->getMemberObject( PlayerComponent::Name );

		if (	playerComponent
			&&	playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) != Tools::Core::Generators::IGenerator::ms_wrongId
			&&	playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) != _playerId
			&&	( *beginWorkers )->getMember< ObjectState::Enum >( ObjectStateKey ) != ObjectState::Dying )
		{
			return false;
		}
	}

	return true;

} // StayAloneChecker::onlyMyOrNeutralObjects


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
