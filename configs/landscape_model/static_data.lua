
-- Resources

StaticData:regResource( QString( "Gold" ) )
StaticData:regResource( QString( "Wood" ) )

-- Elven Archer

elvenArcher = ObjectStaticData()

elvenArcher.m_healthData = HealthComponentStaticData( 100 )
elvenArcher.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground )
elvenArcher.m_moveData = MoveComponentStaticData( 800 )
elvenArcher.m_selectionData = SelectionComponentStaticData( true )

elvenArcher.m_actionsData = ActionsComponentStaticData()
elvenArcher.m_actionsData:can( Actions.Move )

StaticData:regObjectStaticData( QString( "Elven Archer" ), elvenArcher )

-- Grunt

grunt = ObjectStaticData()

grunt.m_healthData = HealthComponentStaticData( 200 )
grunt.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground )
grunt.m_moveData = MoveComponentStaticData( 1000 )
grunt.m_selectionData = SelectionComponentStaticData( true )

grunt.m_actionsData = ActionsComponentStaticData()
grunt.m_actionsData:can( Actions.Move )

StaticData:regObjectStaticData( QString( "Grunt" ), grunt )

-- Orc Barracks

orcBarracks = ObjectStaticData()

orcBarracks.m_healthData = HealthComponentStaticData( 1200 )
orcBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground )
orcBarracks.m_selectionData = SelectionComponentStaticData( true )

orcBarracks.m_actionsData = ActionsComponentStaticData()
orcBarracks.m_actionsData:can( Actions.Build )
orcBarracks.m_actionsData:can( Actions.GenerateResources )

gruntResourceData = ResourcesData()
gruntResourceData:pushResource( QString( "Gold" ), 400 )
gruntResourceData:pushResource( QString( "Wood" ), 200 )

orcBarracks.m_builderData = BuilderComponentStaticData()
orcBarracks.m_builderData:pushBuildObjectData( BuildObjectData( 3000, QString( "Grunt" ), gruntResourceData ) )

orcBarracks.m_generateResourcesData = GenerateResourcesComponentStaticData()
orcBarracks.m_generateResourcesData:canGenerate( QString( "Gold" ), 1000 )
orcBarracks.m_generateResourcesData:canGenerate( QString( "Wood" ), 800 )

StaticData:regObjectStaticData( QString( "Orc Barracks" ), orcBarracks )

-- Human Barracks

humanBarracks = ObjectStaticData()

humanBarracks.m_healthData = HealthComponentStaticData( 1000 )
humanBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground )
humanBarracks.m_selectionData = SelectionComponentStaticData( true )

humanBarracks.m_actionsData = ActionsComponentStaticData()
humanBarracks.m_actionsData:can( Actions.Build )

elvenArcherResourceData = ResourcesData()
elvenArcherResourceData:pushResource( QString( "Gold" ), 300 )
elvenArcherResourceData:pushResource( QString( "Wood" ), 150 )

humanBarracks.m_builderData = BuilderComponentStaticData()
humanBarracks.m_builderData:pushBuildObjectData( BuildObjectData( 4500, QString( "Elven Archer" ), elvenArcherResourceData ) )

StaticData:regObjectStaticData( QString( "Human Barracks" ), humanBarracks )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Static data has been loaded."))