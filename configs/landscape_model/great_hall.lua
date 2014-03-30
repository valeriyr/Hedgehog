
-- Great Hall

greatHall = ObjectStaticData()

greatHall.m_healthData = HealthComponentStaticData( 2500 )
greatHall.m_locateData = LocateComponentStaticData( QSize( 4, 4 ), TerrainMapItem.Ground, Emplacement.Ground )
greatHall.m_selectionData = SelectionComponentStaticData()

peonResourceData = ResourcesData()
peonResourceData:pushResource( QString( "Gold" ), 50 )

greatHall.m_trainData = TrainComponentStaticData()
greatHall.m_trainData:pushTrainData( QString( "Peon" ), TrainData( 1000, peonResourceData ) )

greatHall.m_resourceStorageData = ResourceStorageComponentStaticData()
greatHall.m_resourceStorageData:canStore( QString( "Gold" ) )
greatHall.m_resourceStorageData:canStore( QString( "Wood" ) )

StaticData:regObjectStaticData( QString( "Great Hall" ), greatHall )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Great Hall's static data has been loaded."))