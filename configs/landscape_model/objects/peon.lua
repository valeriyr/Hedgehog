
-- Peon

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 50 )
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

orcBarracksResourceData = ResourcesData()
orcBarracksResourceData:pushResource( QString( "Gold" ), 400 )
orcBarracksResourceData:pushResource( QString( "Wood" ), 200 )

trollLumberMillResourceData = ResourcesData()
trollLumberMillResourceData:pushResource( QString( "Gold" ), 600 )
trollLumberMillResourceData:pushResource( QString( "Wood" ), 400 )

dragonRoostResourceData = ResourcesData()
dragonRoostResourceData:pushResource( QString( "Gold" ), 2500 )
dragonRoostResourceData:pushResource( QString( "Wood" ), 2000 )

greatHallResourceData = ResourcesData()
greatHallResourceData:pushResource( QString( "Gold" ), 1400 )
greatHallResourceData:pushResource( QString( "Wood" ), 1200 )

object.m_buildData = Object()

buildComponentStaticData = BuildComponentStaticData()
buildComponentStaticData:pushBuildData( QString( "Orc Barracks" ), BuildData( 200, orcBarracksResourceData ) )
buildComponentStaticData:pushBuildData( QString( "Troll Lumber Mill" ), BuildData( 300, trollLumberMillResourceData ) )
buildComponentStaticData:pushBuildData( QString( "Dragon Roost" ), BuildData( 600, dragonRoostResourceData ) )
buildComponentStaticData:pushBuildData( QString( "Great Hall" ), BuildData( 400, greatHallResourceData ) )

object.m_buildData:pushBuildStaticDataMember( BuildComponentStaticDataKey, buildComponentStaticData )

StaticData:regObjectStaticData( QString( "Peon" ), object )

-- Object creator

function PeonCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 50 )
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

StaticData:regObjectCreator( QString( "Peon" ), QString( "PeonCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peon's static data has been loaded."))