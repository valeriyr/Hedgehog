
-- Elven Archer

elvenArcher = ObjectStaticData()

elvenArcher.m_healthData = HealthComponentStaticData( 100 )
elvenArcher.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), ISurfaceItemsCache.Ground )
elvenArcher.m_moveData = MoveComponentStaticData( 800 )
elvenArcher.m_selectionData = SelectionComponentStaticData( true )

elvenArcher.m_actionsData = ActionsComponentStaticData()
elvenArcher.m_actionsData:can( ActionsComponentStaticData.Move )

StaticData:regObjectStaticData( QString( "Elven Archer" ), elvenArcher )

-- Grunt

grunt = ObjectStaticData()

grunt.m_healthData = HealthComponentStaticData( 200 )
grunt.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), ISurfaceItemsCache.Ground )
grunt.m_moveData = MoveComponentStaticData( 1000 )
grunt.m_selectionData = SelectionComponentStaticData( true )

grunt.m_actionsData = ActionsComponentStaticData()
grunt.m_actionsData:can( ActionsComponentStaticData.Move )

StaticData:regObjectStaticData( QString( "Grunt" ), grunt )

-- Orc Barracks

orcBarracks = ObjectStaticData()

orcBarracks.m_healthData = HealthComponentStaticData( 1200 )
orcBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), ISurfaceItemsCache.Ground )
orcBarracks.m_selectionData = SelectionComponentStaticData( true )

orcBarracks.m_actionsData = ActionsComponentStaticData()
orcBarracks.m_actionsData:can( ActionsComponentStaticData.Build )

orcBarracks.m_buildData = BuilderComponentStaticData()
orcBarracks.m_buildData:pushBuildObjectData( BuildObjectData( 3000, QString( "Grunt" ) ) )

StaticData:regObjectStaticData( QString( "Orc Barracks" ), orcBarracks )

-- Human Barracks

humanBarracks = ObjectStaticData()

humanBarracks.m_healthData = HealthComponentStaticData( 1000 )
humanBarracks.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), ISurfaceItemsCache.Ground )
humanBarracks.m_selectionData = SelectionComponentStaticData( true )

humanBarracks.m_actionsData = ActionsComponentStaticData()
humanBarracks.m_actionsData:can( ActionsComponentStaticData.Build )

humanBarracks.m_buildData = BuilderComponentStaticData()
humanBarracks.m_buildData:pushBuildObjectData( BuildObjectData( 4500, QString( "Elven Archer" ) ) )

StaticData:regObjectStaticData( QString( "Human Barracks" ), humanBarracks )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Static data has loaded."))