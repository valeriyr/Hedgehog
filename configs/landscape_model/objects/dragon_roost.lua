
-- Dragon Roost

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 1500, true )
object.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_selectionData = SelectionComponentStaticData()
object.m_playerData = PlayerComponentStaticData()

dragonResourceData = ResourcesData()
dragonResourceData:pushResource( QString( "Gold" ), 1400 )
dragonResourceData:pushResource( QString( "Wood" ), 1200 )

object.m_trainData = TrainComponentStaticData()
object.m_trainData:pushTrainData( QString( "Dragon" ), TrainData( 40, dragonResourceData ) )

StaticData:regObjectStaticData( QString( "Dragon Roost" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Dragon Roost's static data has been loaded."))