
-- Resources

StaticData:regResource( QString( "Gold" ) )
StaticData:regResource( QString( "Wood" ) )

-- Peon

peon = ObjectStaticData()

peon.m_healthData = HealthComponentStaticData( 50 )
peon.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
peon.m_moveData = MoveComponentStaticData( 900 )
peon.m_selectionData = SelectionComponentStaticData( true )
peon.m_attackData = AttackComponentStaticData(  4, 6, 1.0, 400, 1500 )

peon.m_actionsData = ActionsComponentStaticData()
peon.m_actionsData:can( Actions.Move )
peon.m_actionsData:can( Actions.Attack )
peon.m_actionsData:can( Actions.Build )

orcBarracksResourceData = ResourcesData()
orcBarracksResourceData:pushResource( QString( "Gold" ), 400 )
orcBarracksResourceData:pushResource( QString( "Wood" ), 200 )

peon.m_buildData = BuildComponentStaticData()
peon.m_buildData:pushBuildData( QString( "Orc Barracks" ), BuildData( 60000, orcBarracksResourceData ) )

StaticData:regObjectStaticData( QString( "Peon" ), peon )

-- Elven Archer

elvenArcher = ObjectStaticData()

elvenArcher.m_healthData = HealthComponentStaticData( 100 )
elvenArcher.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
elvenArcher.m_moveData = MoveComponentStaticData( 800 )
elvenArcher.m_selectionData = SelectionComponentStaticData( true )
elvenArcher.m_attackData = AttackComponentStaticData(  14, 17, 4.0, 500, 1500 )

elvenArcher.m_actionsData = ActionsComponentStaticData()
elvenArcher.m_actionsData:can( Actions.Move )
elvenArcher.m_actionsData:can( Actions.Attack )

StaticData:regObjectStaticData( QString( "Elven Archer" ), elvenArcher )

-- Grunt

grunt = ObjectStaticData()

grunt.m_healthData = HealthComponentStaticData( 200 )
grunt.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
grunt.m_moveData = MoveComponentStaticData( 1000 )
grunt.m_selectionData = SelectionComponentStaticData( true )
grunt.m_attackData = AttackComponentStaticData(  21, 24, 1.0, 500, 1500 )

grunt.m_actionsData = ActionsComponentStaticData()
grunt.m_actionsData:can( Actions.Move )
grunt.m_actionsData:can( Actions.Attack )

StaticData:regObjectStaticData( QString( "Grunt" ), grunt )

-- Dragon

dragon = ObjectStaticData()

dragon.m_healthData = HealthComponentStaticData( 800 )
dragon.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), AnyTerrain, Emplacement.Air )
dragon.m_moveData = MoveComponentStaticData( 1300 )
dragon.m_selectionData = SelectionComponentStaticData( true )
dragon.m_attackData = AttackComponentStaticData(  56, 64, 3.0, 400, 1500 )

dragon.m_actionsData = ActionsComponentStaticData()
dragon.m_actionsData:can( Actions.Move )
dragon.m_actionsData:can( Actions.Attack )

StaticData:regObjectStaticData( QString( "Dragon" ), dragon )

-- Orc Barracks

orcBarracks = ObjectStaticData()

orcBarracks.m_healthData = HealthComponentStaticData( 1200 )
orcBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
orcBarracks.m_selectionData = SelectionComponentStaticData( true )

orcBarracks.m_actionsData = ActionsComponentStaticData()
orcBarracks.m_actionsData:can( Actions.Train )
orcBarracks.m_actionsData:can( Actions.GenerateResources )

gruntResourceData = ResourcesData()
gruntResourceData:pushResource( QString( "Gold" ), 400 )
gruntResourceData:pushResource( QString( "Wood" ), 200 )

dragonResourceData = ResourcesData()
dragonResourceData:pushResource( QString( "Gold" ), 1400 )
dragonResourceData:pushResource( QString( "Wood" ), 1200 )

orcBarracks.m_trainData = TrainComponentStaticData()
orcBarracks.m_trainData:pushTrainData( QString( "Grunt" ), TrainData( 3000, gruntResourceData ) )
orcBarracks.m_trainData:pushTrainData( QString( "Dragon" ), TrainData( 4000, dragonResourceData ) )

orcBarracks.m_generateResourcesData = GenerateResourcesComponentStaticData()
orcBarracks.m_generateResourcesData:canGenerate( QString( "Gold" ), 1000 )
orcBarracks.m_generateResourcesData:canGenerate( QString( "Wood" ), 800 )

StaticData:regObjectStaticData( QString( "Orc Barracks" ), orcBarracks )

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

SystemMessenger:printMessage(IMessenger.Info, QString("Static data has been loaded."))