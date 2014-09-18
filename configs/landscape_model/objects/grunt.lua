
-- Grunt

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 200, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_moveData = MoveComponentStaticData( 10 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData(  21, 24, 15, 5, 15 )
object.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Grunt" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Grunt's static data has been loaded."))