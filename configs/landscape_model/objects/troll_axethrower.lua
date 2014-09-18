
-- Troll Axethrower

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 120, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_moveData = MoveComponentStaticData( 8 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData(  16, 20, 40, 5, 15 )
object.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Troll Axethrower" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Troll Axethrower's static data has been loaded."))