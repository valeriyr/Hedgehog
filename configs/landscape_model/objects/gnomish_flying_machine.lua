
-- Gnomish Flying Machine

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 650, false )
object.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), AnyTerrain, Emplacement.Air )
object.m_moveData = MoveComponentStaticData( 11 )
object.m_selectionData = SelectionComponentStaticData()
object.m_attackData = AttackComponentStaticData(  47, 56, 30, 4, 15 )
object.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Gnomish Flying Machine" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Gnomish Flying Machine's static data has been loaded."))