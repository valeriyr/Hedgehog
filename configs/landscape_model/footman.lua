
-- Footman

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 180, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_moveData = MoveComponentStaticData( 9 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData(  19, 22, 15, 5, 15 )
object.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Footman" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Footman's static data has been loaded."))