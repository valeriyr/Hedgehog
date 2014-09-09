
-- Great Hall

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 2500, true )
object.m_locateData = LocateComponentStaticData( QSize( 4, 4 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_selectionData = SelectionComponentStaticData()
object.m_playerData = PlayerComponentStaticData()

peonResourceData = ResourcesData()
peonResourceData:pushResource( QString( "Gold" ), 50 )

object.m_trainData = TrainComponentStaticData()
object.m_trainData:pushTrainData( QString( "Peon" ), TrainData( 10, peonResourceData ) )

object.m_resourceStorageData = ResourceStorageComponentStaticData()
object.m_resourceStorageData:canStore( QString( "Gold" ) )
object.m_resourceStorageData:canStore( QString( "Wood" ) )

StaticData:regObjectStaticData( QString( "Great Hall" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Great Hall's static data has been loaded."))