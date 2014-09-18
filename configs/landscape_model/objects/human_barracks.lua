
-- Human Barracks

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 1000, true )
object.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_selectionData = SelectionComponentStaticData()
object.m_playerData = PlayerComponentStaticData()

elvenArcherResourceData = ResourcesData()
elvenArcherResourceData:pushResource( QString( "Gold" ), 300 )
elvenArcherResourceData:pushResource( QString( "Wood" ), 100 )

footmanResourceData = ResourcesData()
footmanResourceData:pushResource( QString( "Gold" ), 300 )
footmanResourceData:pushResource( QString( "Wood" ), 100 )

object.m_trainData = TrainComponentStaticData()
object.m_trainData:pushTrainData( QString( "Elven Archer" ), TrainData( 45, elvenArcherResourceData ) )
object.m_trainData:pushTrainData( QString( "Footman" ), TrainData( 35, footmanResourceData ) )

StaticData:regObjectStaticData( QString( "Human Barracks" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Human Barracks's static data has been loaded."))