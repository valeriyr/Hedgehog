
-- Orc Barracks

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 1200, true )
object.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_selectionData = SelectionComponentStaticData()
object.m_playerData = PlayerComponentStaticData()

gruntResourceData = ResourcesData()
gruntResourceData:pushResource( QString( "Gold" ), 400 )
gruntResourceData:pushResource( QString( "Wood" ), 200 )

trollAxethrowerResourceData = ResourcesData()
trollAxethrowerResourceData:pushResource( QString( "Gold" ), 350 )
trollAxethrowerResourceData:pushResource( QString( "Wood" ), 300 )

dragonResourceData = ResourcesData()
dragonResourceData:pushResource( QString( "Gold" ), 1400 )
dragonResourceData:pushResource( QString( "Wood" ), 1200 )

object.m_trainData = TrainComponentStaticData()
object.m_trainData:pushTrainData( QString( "Grunt" ), TrainData( 30, gruntResourceData ) )
object.m_trainData:pushTrainData( QString( "Troll Axethrower" ), TrainData( 40, trollAxethrowerResourceData ) )
object.m_trainData:pushTrainData( QString( "Dragon" ), TrainData( 50, dragonResourceData ) )

StaticData:regObjectStaticData( QString( "Orc Barracks" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Orc Barracks's static data has been loaded."))