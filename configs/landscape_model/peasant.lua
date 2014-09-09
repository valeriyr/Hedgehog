
-- Peasant

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 40, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_moveData = MoveComponentStaticData( 9 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData( 4, 6, 15, 4, 15 )
object.m_repairData = RepairComponentStaticData( 1, 30 )
object.m_playerData = PlayerComponentStaticData()

object.m_resourceHolderData = ResourceHolderComponentStaticData()
object.m_resourceHolderData:hold( QString( "Gold" ), 10, 30 )
object.m_resourceHolderData:hold( QString( "Wood" ), 20, 30 )

humanBarracksResourceData = ResourcesData()
humanBarracksResourceData:pushResource( QString( "Gold" ), 300 )
humanBarracksResourceData:pushResource( QString( "Wood" ), 150 )

townHallResourceData = ResourcesData()
townHallResourceData:pushResource( QString( "Gold" ), 1200 )
townHallResourceData:pushResource( QString( "Wood" ), 1100 )

object.m_buildData = BuildComponentStaticData()
object.m_buildData:pushBuildData( QString( "Human Barracks" ), BuildData( 200, humanBarracksResourceData ) )
object.m_buildData:pushBuildData( QString( "Town Hall" ), BuildData( 400, townHallResourceData ) )

StaticData:regObjectStaticData( QString( "Peasant" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peasant's static data has been loaded."))