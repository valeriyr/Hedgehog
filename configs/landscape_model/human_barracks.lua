
-- Human Barracks

humanBarracks = ObjectStaticData()

humanBarracks.m_healthData = HealthComponentStaticData( 1000, true )
humanBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
humanBarracks.m_selectionData = SelectionComponentStaticData()
humanBarracks.m_playerData = PlayerComponentStaticData()

elvenArcherResourceData = ResourcesData()
elvenArcherResourceData:pushResource( QString( "Gold" ), 300 )
elvenArcherResourceData:pushResource( QString( "Wood" ), 100 )

humanBarracks.m_trainData = TrainComponentStaticData()
humanBarracks.m_trainData:pushTrainData( QString( "Elven Archer" ), TrainData( 45, elvenArcherResourceData ) )

StaticData:regObjectStaticData( QString( "Human Barracks" ), humanBarracks )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Human Barracks's static data has been loaded."))