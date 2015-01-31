
#ifndef __LM_COMPONENTS_HPP__
#define __LM_COMPONENTS_HPP__

#include "object/tl_object.hpp"


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
		qint32& maxHealth = _healthComponent.getMember< qint32 >( StaticDataTools::generateName( StaticData::MaxHealth ) );
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
		qint32& maxHealth = _healthComponent.getMember< qint32 >( StaticDataTools::generateName( StaticData::MaxHealth ) );
		qint32& health = _healthComponent.getMember< qint32 >( Health );

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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMPONENTS_HPP__
