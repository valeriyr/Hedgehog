
#ifndef __LM_COMPONENTS_HPP__
#define __LM_COMPONENTS_HPP__

#include "object/tl_object.hpp"
#include "generators/gn_igenerator.hpp"

#include "landscape_model/h/lm_constants.hpp"
#include "landscape_model/h/lm_resources_data.hpp"
#include "landscape_model/h/lm_directions.hpp"
#include "landscape_model/h/lm_terrain_map_data.hpp"

#include "landscape_model/sources/path_finders/lm_ipath_finder.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class GameObject;

/*---------------------------------------------------------------------------*/

namespace StaticDataTools
{
	const QString Name = "StaticDataName";

	inline QString generateName( const QString& _variableName )
	{
		return Tools::Core::Object::generateName( Name, _variableName );
	}
}

/*---------------------------------------------------------------------------*/

namespace AttackComponent
{
	const QString Name = "AttackComponent";

	namespace StaticData
	{
		const QString MinDamage = "MinDamage";
		const QString MaxDamage = "MaxDamage";
		const QString Distance = "Distance";
		const QString Aiming = "Aiming";
		const QString Reloading = "Reloading";
	}

	const QString TargetObject = "TargetObject";
}

/*---------------------------------------------------------------------------*/

namespace SelectionComponent
{
	const QString Name = "SelectionComponent";
	const QString IsSelected = "IsSelected";
}

/*---------------------------------------------------------------------------*/

namespace HealthComponent
{
	const QString Name = "HealthComponent";

	namespace StaticData
	{
		const QString MaxHealth = "MaxHealth";
		const QString CanBeRepair = "CanBeRepair";
	}

	const QString Health = "Health";

	//const QString SetHealth = "SetHealth";
	//const QString IsHealthy = "IsHealthy";

	static void setHealth( Tools::Core::Object& _healthComponent, const qint32 _health )
	{
		const qint32& maxHealth = _healthComponent.getMember< qint32 >( StaticDataTools::generateName( StaticData::MaxHealth ) );
		qint32& health = _healthComponent.getMember< qint32 >( Health );

		if ( _health < 0 )
			health = 0;
		else if ( _health > maxHealth )
			health = maxHealth;
		else
			health = _health;
	}

	static bool isHealthy( Tools::Core::Object& _healthComponent )
	{
		const qint32& maxHealth = _healthComponent.getMember< qint32 >( StaticDataTools::generateName( StaticData::MaxHealth ) );
		const qint32& health = _healthComponent.getMember< qint32 >( Health );

		return health == maxHealth;
	}
}

/*---------------------------------------------------------------------------*/

namespace PlayerComponent
{
	const QString Name = "PlayerComponent";
	const QString PlayerId = "PlayerId";
}

/*---------------------------------------------------------------------------*/

namespace GenerateResourcesComponent
{
	const QString Name = "GenerateResourcesComponent";

	namespace StaticData
	{
		const QString ResourcesByTick = "ResourcesByTick";
	}
}

/*---------------------------------------------------------------------------*/

namespace BuildComponent
{
	const QString Name = "BuildComponent";

	namespace StaticData
	{
		const QString DataKey = "DataKey";

		struct Data
		{
			typedef boost::shared_ptr< Data > Ptr;

			struct BuildData
			{
				BuildData(
						const TickType _ticksCount
					,	const ResourcesData& _resourcesData
					)
					:	m_ticksCount( _ticksCount )
					,	m_resourcesData( _resourcesData )
				{}

				const TickType m_ticksCount;
				const ResourcesData m_resourcesData;
			};

			typedef
				std::map< QString, boost::shared_ptr< const BuildData > >
				BuildDataCollection;
			typedef
				BuildDataCollection::const_iterator
				BuildDataCollectionIterator;

			Data()
				:	m_buildDatas()
			{}

			void pushBuildData( const QString& _objectName, boost::shared_ptr< BuildData > _data )
			{
				m_buildDatas.insert( std::make_pair( _objectName, _data ) );
			}

			BuildDataCollection m_buildDatas;
		};
	}

	const QString ObjectName = "ObjectName";
	const QString AtRect = "AtRect";
	const QString BuildProgress = "BuildProgress";
	const QString ObjectId = "ObjectId";

	static void clearData( Tools::Core::Object& _buildComponent )
	{
		_buildComponent.getMember< QString >( ObjectName ).clear();
		_buildComponent.getMember< QRect >( AtRect ) = QRect();
		_buildComponent.getMember< TickType >( BuildProgress ) = 0;
		_buildComponent.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectId ) = Tools::Core::Generators::IGenerator::ms_wrongId;
	}
}

/*---------------------------------------------------------------------------*/

namespace LocateComponent
{
	const QString Name = "LocateComponent";

	namespace StaticData
	{
		const QString Size = "Size";
		const QString Passability = "Passability";
		const QString Emplacement = "Emplacement";
	}

	const QString Direction = "Direction";
	const QString Location = "Location";
	const QString IsHidden = "IsHidden";

	static const QRect getRect( Tools::Core::Object& _locateComponent )
	{
		return QRect( _locateComponent.getMember< QPoint >( Location ), _locateComponent.getMember< QSize >( StaticDataTools::generateName( StaticData::Size ) ) );
	}
}

/*---------------------------------------------------------------------------*/

namespace MoveComponent
{
	const QString Name = "MoveComponent";

	namespace StaticData
	{
		const QString MovingSpeed = "MovingSpeed";
	}

	const QString Path = "Path";
	const QString MovingProgress = "MovingProgress";
	const QString MovingTo = "MovingTo";
	const QString MovingToObject = "MovingToObject";

	static void clearData( Tools::Core::Object& _moveComponent )
	{
		_moveComponent.getMember< IPathFinder::PointsCollection >( Path ).clear();
		_moveComponent.getMember< TickType >( MovingProgress ) = 0;
		_moveComponent.getMember< QPoint >( MovingTo ) = QPoint( 0, 0 );
		_moveComponent.getMember< boost::shared_ptr< GameObject > >( MovingToObject ).reset();
	}

	static void leaveOnlyFirstPoint( Tools::Core::Object& _moveComponent )
	{
		IPathFinder::PointsCollection& path = _moveComponent.getMember< IPathFinder::PointsCollection >( Path );

		if ( !path.empty() )
		{
			QPoint inProgressPoint( path.front() );
			path.clear();
			path.push_back( inProgressPoint );
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace RepairComponent
{
	const QString Name = "RepairComponent";

	namespace StaticData
	{
		const QString HealthByTick = "HealthByTick";
		const QString CostPercent = "CostPercent";		/* 0 - 100 */
	}

	const QString TargetObject = "TargetObject";
}

/*---------------------------------------------------------------------------*/

namespace ResourceHolderComponent
{
	const QString Name = "ResourceHolderComponent";

	namespace StaticData
	{
		const QString HoldStaticDataKey = "HoldStaticDataKey";

		struct HoldResourceData
		{
			HoldResourceData( const int _maxValue, const int _collectTime )
				:	m_maxValue( _maxValue )
				,	m_collectTime( _collectTime )
			{}

			const int m_maxValue;
			const int m_collectTime;
		};

		struct HoldStaticData
		{
			HoldStaticData()
				:	m_holdResourceData()
			{}

			void pushData( const QString& _resourceName, const HoldResourceData& _data )
			{
				if ( m_holdResourceData.find( _resourceName ) == m_holdResourceData.end() )
					m_holdResourceData.insert( std::make_pair( _resourceName, _data ) );
			}

			const HoldResourceData& getData( const QString& _resourceName ) const
			{
				HoldResourceDataCollectionIterator iterator = m_holdResourceData.find( _resourceName );

				assert( iterator != m_holdResourceData.end() );

				return iterator->second;
			}

			typedef std::map< QString, HoldResourceData > HoldResourceDataCollection;
			typedef HoldResourceDataCollection::const_iterator HoldResourceDataCollectionIterator;

			HoldResourceDataCollection m_holdResourceData;
		};
	}

	const QString HeldResources = "HeldResources";

	static void initComponent( Tools::Core::Object& _resourceHolderComponent )
	{
		const StaticData::HoldStaticData& holderData
			= _resourceHolderComponent.getMember< StaticData::HoldStaticData >( StaticDataTools::generateName( StaticData::HoldStaticDataKey ) );

		StaticData::HoldStaticData::HoldResourceDataCollectionIterator
				begin = holderData.m_holdResourceData.begin()
			,	end = holderData.m_holdResourceData.end();

		for ( ; begin != end; ++begin )
			_resourceHolderComponent.getMember< ResourcesData >( HeldResources ).pushResource( begin->first, 0 );
	}

	static bool isFull( Tools::Core::Object& _resourceHolderComponent, const QString& _resourceName )
	{
		StaticData::HoldStaticData::HoldResourceDataCollectionIterator
			iterator = _resourceHolderComponent.getMember< StaticData::HoldStaticData >( StaticDataTools::generateName( StaticData::HoldStaticDataKey ) ).m_holdResourceData.find( _resourceName );

		assert( _resourceHolderComponent.getMember< ResourcesData >( HeldResources ).getResourceValue( _resourceName ) <= iterator->second.m_maxValue );

		return _resourceHolderComponent.getMember< ResourcesData >( HeldResources ).getResourceValue( _resourceName ) == iterator->second.m_maxValue;
	}
}

/*---------------------------------------------------------------------------*/

namespace ResourceSourceComponent
{
	const QString Name = "ResourceSourceComponent";

	namespace StaticData
	{
		const QString ResourceType = "ResourceType";
	}

	const QString ResourceValue = "ResourceValue";
	const QString ObjectInside = "ObjectInside";

	static void setResourceValue( Tools::Core::Object& _resourceSourceComponent, const qint32 _value )
	{
		_resourceSourceComponent.getMember< qint32 >( ResourceValue ) = std::max( 0 , _value );
	}
}

/*---------------------------------------------------------------------------*/

namespace ResourceStorageComponent
{
	const QString Name = "ResourceStorageComponent";

	namespace StaticData
	{
		const QString PossibleToStore = "PossibleToStore";

		struct PossibleToStoreData
		{
			typedef std::set< QString > PossibleToStoreDataCollection;
			typedef PossibleToStoreDataCollection::const_iterator PossibleToStoreDataCollectionIterator;

			PossibleToStoreData()
				:	m_possibleToStoreData()
			{}

			void canStore( const QString& _resourceName )
			{
				m_possibleToStoreData.insert( _resourceName );
			}

			bool canBeStored( const QString& _resourceName ) const
			{
				return m_possibleToStoreData.find( _resourceName ) != m_possibleToStoreData.end();
			}

			PossibleToStoreDataCollection m_possibleToStoreData;
		};
	}
}

/*---------------------------------------------------------------------------*/

namespace TrainComponent
{
	const QString Name = "TrainComponent";

	namespace StaticData
	{
		const QString DataKey = "DataKey";

		struct Data
		{
			typedef boost::shared_ptr< Data > Ptr;

			struct TrainData
			{
				TrainData(
						const TickType _creationTime
					,	const ResourcesData& _resourcesData
					)
					:	m_creationTime( _creationTime )
					,	m_resourcesData( _resourcesData )
				{}

				const TickType m_creationTime;
				const ResourcesData m_resourcesData;
			};

			typedef
				std::map< QString, boost::shared_ptr< const TrainData > >
				TrainDataCollection;
			typedef
				TrainDataCollection::const_iterator
				TrainDataCollectionIterator;

			Data()
				:	m_trainObjects()
			{}

			void pushTrainData( const QString _objectName, boost::shared_ptr< TrainData > _data )
			{
				m_trainObjects.insert( std::make_pair( _objectName, _data ) );
			}

			TrainDataCollection m_trainObjects;
		};
	}

	const QString Progress = "Progress";

	struct ProgressData
	{
		ProgressData()
			:	m_trainProgress( 0 )
			,	m_trainingObjectName()
		{}

		void reset()
		{
			 m_trainProgress = 0;
			 m_trainingObjectName.clear();
		}

		TickType m_trainProgress;

		QString m_trainingObjectName;
	};
}

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMPONENTS_HPP__
