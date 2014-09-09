
-- Peon

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 50, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_moveData = MoveComponentStaticData( 9 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData( 4, 6, 15, 4, 15 )
object.m_repairData = RepairComponentStaticData( 1, 30 )
object.m_playerData = PlayerComponentStaticData()

object.m_resourceHolderData = ResourceHolderComponentStaticData()
object.m_resourceHolderData:hold( QString( "Gold" ), 10, 30 )
object.m_resourceHolderData:hold( QString( "Wood" ), 20, 30 )

orcBarracksResourceData = ResourcesData()
orcBarracksResourceData:pushResource( QString( "Gold" ), 400 )
orcBarracksResourceData:pushResource( QString( "Wood" ), 200 )

trollLumberMillResourceData = ResourcesData()
trollLumberMillResourceData:pushResource( QString( "Gold" ), 600 )
trollLumberMillResourceData:pushResource( QString( "Wood" ), 400 )

greatHallResourceData = ResourcesData()
greatHallResourceData:pushResource( QString( "Gold" ), 1400 )
greatHallResourceData:pushResource( QString( "Wood" ), 1200 )

object.m_buildData = BuildComponentStaticData()
object.m_buildData:pushBuildData( QString( "Orc Barracks" ), BuildData( 200, orcBarracksResourceData ) )
object.m_buildData:pushBuildData( QString( "Troll Lumber Mill" ), BuildData( 300, trollLumberMillResourceData ) )
object.m_buildData:pushBuildData( QString( "Great Hall" ), BuildData( 400, greatHallResourceData ) )

StaticData:regObjectStaticData( QString( "Peon" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peon's static data has been loaded."))