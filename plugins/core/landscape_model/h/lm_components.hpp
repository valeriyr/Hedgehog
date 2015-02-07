
#ifndef __LM_COMPONENTS_HPP__
#define __LM_COMPONENTS_HPP__

#include "object/tl_object.hpp"
#include "generators/gn_igenerator.hpp"

#include "landscape_model/h/lm_constants.hpp"
#include "landscape_model/h/lm_resources_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMPONENTS_HPP__