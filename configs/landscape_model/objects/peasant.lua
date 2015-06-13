
-- Peasant

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 40 )
object.m_healthData:pushBoolMember( HealthComponentCanBeRepair, false )
--object.m_healthData:pushBoolMethod( HealthComponentIsHealthy, HealthComponentIsHealthyDefault )
--object.m_healthData:pushVoidIntMethod( HealthComponentSetHealth, HealthComponentSetHealthDefault )

object.m_locateData = Object()
object.m_locateData:pushSizeMember( LocateComponentSize, QSize( 1, 1 ) )
object.m_locateData:pushIntMember( LocateComponentPassability, TerrainMapItem.Ground )
object.m_locateData:pushEmplacementMember( LocateComponentEmplacement, Emplacement.Ground )

object.m_moveData = Object()
object.m_moveData:pushTickTypeMember( MoveComponentMovingSpeed, 9 )

object.m_selectionData = Object()
object.m_playerData = Object()

object.m_attackData = Object()
object.m_attackData:pushIntMember( AttackComponentDistance, 15 )
object.m_attackData:pushIntMember( AttackComponentMinDamage, 4 )
object.m_attackData:pushIntMember( AttackComponentMaxDamage, 6 )
object.m_attackData:pushTickTypeMember( AttackComponentAiming, 4 )
object.m_attackData:pushTickTypeMember( AttackComponentReloading, 15 )

object.m_repairData = Object()
object.m_repairData:pushTickTypeMember( RepairComponentHealthByTick, 1 )
object.m_repairData:pushIntMember( RepairComponentCostPercent, 30 )

object.m_resourceHolderData = Object()

holdStaticData = HoldStaticData()
holdStaticData:pushData( QString( "Gold" ), HoldResourceData( 10, 30 ) )
holdStaticData:pushData( QString( "Wood" ), HoldResourceData( 20, 30 ) )

object.m_resourceHolderData:pushHoldStaticDataMember( ResourceHolderComponentHoldStaticData, holdStaticData )

humanBarracksResourceData = ResourcesData()
humanBarracksResourceData:pushResource( QString( "Gold" ), 300 )
humanBarracksResourceData:pushResource( QString( "Wood" ), 150 )

foundryResourceData = ResourcesData()
foundryResourceData:pushResource( QString( "Gold" ), 700 )
foundryResourceData:pushResource( QString( "Wood" ), 550 )

townHallResourceData = ResourcesData()
townHallResourceData:pushResource( QString( "Gold" ), 1200 )
townHallResourceData:pushResource( QString( "Wood" ), 1100 )

object.m_buildData = Object()

buildComponentStaticData = BuildComponentStaticData()
buildComponentStaticData:pushBuildData( QString( "Human Barracks" ), BuildData( 200, humanBarracksResourceData ) )
buildComponentStaticData:pushBuildData( QString( "Foundry" ), BuildData( 600, foundryResourceData ) )
buildComponentStaticData:pushBuildData( QString( "Town Hall" ), BuildData( 400, townHallResourceData ) )

object.m_buildData:pushBuildStaticDataMember( BuildComponentStaticDataKey, buildComponentStaticData )

StaticData:regObjectStaticData( QString( "Peasant" ), object )

-- Object creator

function PeasantCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 40 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )
	gameObject:getObjectPtrMember( AttackComponentName ):pushGameObjectPtrMember( AttackComponentTargetObject, GameObjectPtr() )

	gameObject:getObjectPtrMember( BuildComponentName ):pushStringMember( BuildComponentObjectName, QString() )
	gameObject:getObjectPtrMember( BuildComponentName ):pushRectMember( BuildComponentAtRect, QRect() )
	gameObject:getObjectPtrMember( BuildComponentName ):pushTickTypeMember( BuildComponentBuildProgress, 0 )
	gameObject:getObjectPtrMember( BuildComponentName ):pushIntMember( BuildComponentObjectId, 0 )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( MoveComponentName ):pushListOfPointsMember( MoveComponentPath, ListOfPoints() )
	gameObject:getObjectPtrMember( MoveComponentName ):pushTickTypeMember( MoveComponentMovingProgress, 0 )
	gameObject:getObjectPtrMember( MoveComponentName ):pushPointMember( MoveComponentMovingTo, QPoint() )
	gameObject:getObjectPtrMember( MoveComponentName ):pushGameObjectPtrMember( MoveComponentMovingToObject, GameObjectPtr() )

	gameObject:getObjectPtrMember( RepairComponentName ):pushGameObjectPtrMember( RepairComponentTargetObject, GameObjectPtr() )

	gameObject:getObjectPtrMember( ResourceHolderComponentName ):pushResourcesDataMember( ResourceHolderComponentHeldResources, ResourcesData() )
	initResourceHolderComponent( gameObject:getObjectPtrMember( ResourceHolderComponentName ) )

end

StaticData:regObjectCreator( QString( "Peasant" ), QString( "PeasantCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peasant's static data has been loaded."))