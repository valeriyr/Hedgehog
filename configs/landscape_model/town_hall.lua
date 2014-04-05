
-- Town Hall

townHall = ObjectStaticData()

townHall.m_healthData = HealthComponentStaticData( 2100, true )
townHall.m_locateData = LocateComponentStaticData( QSize( 4, 4 ), TerrainMapItem.Ground, Emplacement.Ground )
townHall.m_selectionData = SelectionComponentStaticData()
townHall.m_playerData = PlayerComponentStaticData()

peasantResourceData = ResourcesData()
peasantResourceData:pushResource( QString( "Gold" ), 50 )

townHall.m_trainData = TrainComponentStaticData()
townHall.m_trainData:pushTrainData( QString( "Peasant" ), TrainData( 10, peasantResourceData ) )

townHall.m_resourceStorageData = ResourceStorageComponentStaticData()
townHall.m_resourceStorageData:canStore( QString( "Gold" ) )
townHall.m_resourceStorageData:canStore( QString( "Wood" ) )

StaticData:regObjectStaticData( QString( "Town Hall" ), townHall )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Town Hall's static data has been loaded."))