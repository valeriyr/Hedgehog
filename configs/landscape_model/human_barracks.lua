
-- Human Barracks

humanBarracks = ObjectStaticData()

humanBarracks.m_healthData = HealthComponentStaticData( 1000 )
humanBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
humanBarracks.m_selectionData = SelectionComponentStaticData( true )

humanBarracks.m_actionsData = ActionsComponentStaticData()
humanBarracks.m_actionsData:can( Actions.Train )

elvenArcherResourceData = ResourcesData()
elvenArcherResourceData:pushResource( QString( "Gold" ), 300 )
elvenArcherResourceData:pushResource( QString( "Wood" ), 100 )

humanBarracks.m_trainData = TrainComponentStaticData()
humanBarracks.m_trainData:pushTrainData( QString( "Elven Archer" ), TrainData( 4500, elvenArcherResourceData ) )

StaticData:regObjectStaticData( QString( "Human Barracks" ), humanBarracks )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Human Barracks's static data has been loaded."))