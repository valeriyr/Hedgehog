
-- Orc Barracks

orcBarracks = ObjectStaticData()

orcBarracks.m_healthData = HealthComponentStaticData( 1200, true )
orcBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
orcBarracks.m_selectionData = SelectionComponentStaticData()
orcBarracks.m_playerData = PlayerComponentStaticData()

gruntResourceData = ResourcesData()
gruntResourceData:pushResource( QString( "Gold" ), 400 )
gruntResourceData:pushResource( QString( "Wood" ), 200 )

dragonResourceData = ResourcesData()
dragonResourceData:pushResource( QString( "Gold" ), 1400 )
dragonResourceData:pushResource( QString( "Wood" ), 1200 )

orcBarracks.m_trainData = TrainComponentStaticData()
orcBarracks.m_trainData:pushTrainData( QString( "Grunt" ), TrainData( 30, gruntResourceData ) )
orcBarracks.m_trainData:pushTrainData( QString( "Dragon" ), TrainData( 40, dragonResourceData ) )

StaticData:regObjectStaticData( QString( "Orc Barracks" ), orcBarracks )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Orc Barracks's static data has been loaded."))