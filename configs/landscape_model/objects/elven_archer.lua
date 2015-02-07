
-- Elven Archer

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 100, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_moveData = MoveComponentStaticData( 7 )
object.m_selectionData = SelectionComponentStaticData()

attackComponent = Object()
attackComponent:pushGameObjectPtrMember( AttackComponentTargetObject, GameObjectPtr() )
attackComponent:pushIntMember( AttackComponentDistance, 40 )
attackComponent:pushIntMember( AttackComponentMinDamage, 14 )
attackComponent:pushIntMember( AttackComponentMaxDamage, 17 )
attackComponent:pushTickTypeMember( AttackComponentAiming, 5 )
attackComponent:pushTickTypeMember( AttackComponentReloading, 15 )

object.m_attackData = attackComponent
object.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Elven Archer" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Elven Archer's static data has been loaded."))