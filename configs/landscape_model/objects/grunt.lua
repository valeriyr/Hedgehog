
-- Grunt

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 200 )
object.m_healthData:pushBoolMember( HealthComponentCanBeRepair, false )
--object.m_healthData:pushBoolMethod( HealthComponentIsHealthy, HealthComponentIsHealthyDefault )
--object.m_healthData:pushVoidIntMethod( HealthComponentSetHealth, HealthComponentSetHealthDefault )

object.m_locateData = Object()
object.m_locateData:pushSizeMember( LocateComponentSize, QSize( 1, 1 ) )
object.m_locateData:pushIntMember( LocateComponentPassability, TerrainMapItem.Ground )
object.m_locateData:pushEmplacementMember( LocateComponentEmplacement, Emplacement.Ground )

object.m_selectionData = Object()
object.m_playerData = Object()

object.m_moveData = Object()
object.m_moveData:pushTickTypeMember( MoveComponentMovingSpeed, 10 )

object.m_attackData = Object()
object.m_attackData:pushIntMember( AttackComponentDistance, 15 )
object.m_attackData:pushIntMember( AttackComponentMinDamage, 21 )
object.m_attackData:pushIntMember( AttackComponentMaxDamage, 24 )
object.m_attackData:pushTickTypeMember( AttackComponentAiming, 5 )
object.m_attackData:pushTickTypeMember( AttackComponentReloading, 15 )

StaticData:regObjectStaticData( QString( "Grunt" ), object )

-- Object creator

function GruntCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 200 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )
	gameObject:getObjectPtrMember( AttackComponentName ):pushGameObjectPtrMember( AttackComponentTargetObject, GameObjectPtr() )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( MoveComponentName ):pushListOfPointsMember( MoveComponentPath, ListOfPoints() )
	gameObject:getObjectPtrMember( MoveComponentName ):pushTickTypeMember( MoveComponentMovingProgress, 0 )
	gameObject:getObjectPtrMember( MoveComponentName ):pushPointMember( MoveComponentMovingTo, QPoint() )
	gameObject:getObjectPtrMember( MoveComponentName ):pushGameObjectPtrMember( MoveComponentMovingToObject, GameObjectPtr() )

end

StaticData:regObjectCreator( QString( "Grunt" ), QString( "GruntCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Grunt's static data has been loaded."))