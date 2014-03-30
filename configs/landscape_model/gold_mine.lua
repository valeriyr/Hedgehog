
-- Gold Mine

goldMine = ObjectStaticData()

goldMine.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
goldMine.m_selectionData = SelectionComponentStaticData()
goldMine.m_resourceHolderData = ResourceHolderComponentStaticData( QString( "Gold" ) )

StaticData:regObjectStaticData( QString( "Gold Mine" ), goldMine )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Gold Mine's static data has been loaded."))