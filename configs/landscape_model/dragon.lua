
-- Dragon

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 800, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), AnyTerrain, Emplacement.Air )
object.m_moveData = MoveComponentStaticData( 13 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData(  56, 64, 30, 4, 15 )
object.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Dragon" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Dragon's static data has been loaded."))