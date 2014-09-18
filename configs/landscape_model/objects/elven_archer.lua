
-- Elven Archer

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 100, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_moveData = MoveComponentStaticData( 7 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData(  14, 17, 40, 5, 15 )
object.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Elven Archer" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Elven Archer's static data has been loaded."))