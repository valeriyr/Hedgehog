
#ifndef __LM_ILANDSCAPE_MODEL_HPP__
#define __LM_ILANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_iplayer.hpp"

#include "landscape_model/h/lm_object.hpp"
#include "landscape_model/h/lm_commands.hpp"
#include "landscape_model/h/lm_victory_condition.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace Core
	{
		namespace NetworkManager
		{
			struct ConnectionInfo;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModel
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void initLandscape( const QString& _filePath ) = 0;

	virtual void setupMultiPlayerGame() = 0;

	virtual void connectToMultiPlayerGame( const Framework::Core::NetworkManager::ConnectionInfo& _connectTo ) = 0;

	virtual void setupSinglePlayerGame() = 0;

	virtual void resetModel() = 0;

	virtual void saveModel( const QString& _filePath ) = 0;

	virtual bool isSimulationRunning() const = 0;

	virtual bool isConfigurated() const = 0;

	virtual const QString& getFilePath() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const VictoryCondition::Enum getVictoryConditionType() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushCommand( const Command& _command ) = 0;

	COMMAND_MAP_DECLARE_INTERFACE()

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< QString >
		TrainObjectsList;
	typedef
		TrainObjectsList::const_iterator
		TrainObjectsListIterator;

	virtual void getTrainObjectsList( boost::shared_ptr< Object > _forObject, TrainObjectsList& _list ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ILandscape > getLandscape() const = 0;

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< boost::intrusive_ptr< IPlayer > >
		PlayersCollection;
	typedef
		PlayersCollection::const_iterator
		PlayersCollectionIterator;

	virtual boost::intrusive_ptr< IPlayer > getPlayer( const IPlayer::Id& _id ) const = 0;

	virtual boost::intrusive_ptr< IPlayer > getPlayer( const Object& _object ) const = 0;

	virtual boost::intrusive_ptr< IPlayer > getPlayer( const QString& _name ) const = 0;

	virtual boost::intrusive_ptr< IPlayer > getPlayerByStartPoint( const StartPoint::Id& _id ) const = 0;

	virtual boost::intrusive_ptr< IPlayer > getMyPlayer() const = 0;

	virtual boost::intrusive_ptr< IPlayer > getFirstFreePlayer() const = 0;

	virtual void fetchPlayers( PlayersCollection& _collection ) const = 0;

	virtual bool twoOrMoreActivatedPlayers() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
