
#ifndef __LM_ILANDSCAPE_MODEL_HPP__
#define __LM_ILANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_iplayer.hpp"

#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModel
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct PlayerStartupData
	{
		PlayerStartupData( const QString& _race, const StartPoint::Id& _startPointId )
			:	m_race( _race )
			,	m_startPointId( _startPointId )
		{}

		const QString m_race;

		const StartPoint::Id m_startPointId;
	};

	typedef
		std::vector< PlayerStartupData >
		PlayersSturtupDataCollection;
	typedef
		PlayersSturtupDataCollection::const_iterator
		PlayersSturtupDataCollectionIterator;

/*---------------------------------------------------------------------------*/

	virtual void initLandscape( const QString& _filePath ) = 0;

	virtual void initPlayers( const QString& _filePath, const PlayersSturtupDataCollection& _data ) = 0;

	virtual void resetModel() = 0;

	virtual void saveModel( const QString& _filePath ) = 0;

	virtual void startSimulation() = 0;

/*---------------------------------------------------------------------------*/

	virtual void selectObjects( const QRect& _rect ) = 0;

	virtual void selectObject( const Object::Id& _id ) = 0;

	virtual void sendSelectedObjects( const QPoint& _to, const bool _flush ) = 0;

	virtual void createObject( const QPoint& _location, const QString& _objectName, const IPlayer::Id& _playerId ) = 0;

	virtual void setSurfaceItem(
			const QPoint& _location
		,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) = 0;

	virtual void trainObject( const Object::Id& _parentObject, const QString& _objectName ) = 0;

	virtual void buildObject(
			const Object::Id& _builder
		,	const QString& _objectName
		,	const QPoint& _atLocation
		,	const bool _flush ) = 0;

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
		boost::shared_ptr< Tools::Core::IIterator< boost::intrusive_ptr< IPlayer > > >
		PlayersIterator;

	virtual boost::intrusive_ptr< IPlayer > getPlayer( const IPlayer::Id& _id ) const = 0;

	virtual boost::intrusive_ptr< IPlayer > getPlayerByStartPoint( const StartPoint::Id& _id ) const = 0;

	virtual boost::intrusive_ptr< IPlayer > getMyPlayer() const = 0;

	virtual PlayersIterator getPlayersIterator() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_HPP__
