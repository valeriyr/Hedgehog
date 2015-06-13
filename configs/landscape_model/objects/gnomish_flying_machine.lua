
-- Gnomish Flying Machine

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 650 )
object.m_healthData:pushBoolMember( HealthComponentCanBeRepair, true )
--object.m_healthData:pushBoolMethod( HealthComponentIsHealthy, HealthComponentIsHealthyDefault )
--object.m_healthData:pushVoidIntMethod( HealthComponentSetHealth, HealthComponentSetHealthDefault )

object.m_locateData = Object()
object.m_locateData:pushSizeMember( LocateComponentSize, QSize( 1, 1 ) )
object.m_locateData:pushIntMember( LocateComponentPassability, AnyTerrain )
object.m_locateData:pushEmplacementMember( LocateComponentEmplacement, Emplacement.Air )

object.m_selectionData = Object()
object.m_playerData = Object()

object.m_moveData = Object()
object.m_moveData:pushTickTypeMember( MoveComponentMovingSpeed, 11 )

object.m_attackData = Object()
object.m_attackData:pushIntMember( AttackComponentDistance, 30 )
object.m_attackData:pushIntMember( AttackComponentMinDamage, 47 )
object.m_attackData:pushIntMember( AttackComponentMaxDamage, 56 )
object.m_attackData:pushTickTypeMember( AttackComponentAiming, 4 )
object.m_attackData:pushTickTypeMember( AttackComponentReloading, 15 )

StaticData:regObjectStaticData( QString( "Gnomish Flying Machine" ), object )

-- Object creator

function GnomishFlyingMachineCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 650 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )
	gameObject:getObjectPtrMember( AttackComponentName ):pushGameObjectPtrMember( AttackComponentTargetObject, GameObjectPtr() )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( MoveComponentName ):pushListOfPointsMember( MoveComponentPath, ListOfPoints() )
	gameObject:getObjectPtrMember( MoveComponentName ):pushTickTypeMember( MoveComponentMovingProgress, 0 )
	gameObject:getObjectPtrMember( MoveComponentName ):pushPointMember( MoveComponentMovingTo, QPoint() )
	gameObject:getObjectPtrMember( MoveComponentName ):pushGameObjectPtrMember( MoveComponentMovingToObject, GameObjectPtr() )

end

StaticData:regObjectCreator( QString( "Gnomish Flying Machine" ), QString( "GnomishFlyingMachineCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Gnomish Flying Machine's static data has been loaded."))