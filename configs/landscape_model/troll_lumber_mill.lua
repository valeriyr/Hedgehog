
-- Troll Lumber Mill

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 900, true )
object.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_selectionData = SelectionComponentStaticData()
object.m_playerData = PlayerComponentStaticData()

trollAxethrowerResourceData = ResourcesData()
trollAxethrowerResourceData:pushResource( QString( "Gold" ), 350 )
trollAxethrowerResourceData:pushResource( QString( "Wood" ), 300 )

object.m_trainData = TrainComponentStaticData()
object.m_trainData:pushTrainData( QString( "Troll Axethrower" ), TrainData( 40, trollAxethrowerResourceData ) )

StaticData:regObjectStaticData( QString( "Troll Lumber Mill" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Troll Lumber Mill's static data has been loaded."))