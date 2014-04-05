
-- Peasant

peasant = ObjectStaticData()

peasant.m_healthData = HealthComponentStaticData( 40, false )
peasant.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
peasant.m_moveData = MoveComponentStaticData( 9 )
peasant.m_selectionData = SelectionComponentStaticData()
peasant.m_attackData = AttackComponentStaticData( 4, 6, 15, 4, 15 )
peasant.m_repairData = RepairComponentStaticData( 1, 30 )
peasant.m_playerData = PlayerComponentStaticData()

peasant.m_resourceHolderData = ResourceHolderComponentStaticData()
peasant.m_resourceHolderData:hold( QString( "Gold" ), 10, 30 )
peasant.m_resourceHolderData:hold( QString( "Wood" ), 20, 30 )

humanBarracksResourceData = ResourcesData()
humanBarracksResourceData:pushResource( QString( "Gold" ), 300 )
humanBarracksResourceData:pushResource( QString( "Wood" ), 150 )

greatHallResourceData = ResourcesData()
greatHallResourceData:pushResource( QString( "Gold" ), 1400 )
greatHallResourceData:pushResource( QString( "Wood" ), 1200 )

peasant.m_buildData = BuildComponentStaticData()
peasant.m_buildData:pushBuildData( QString( "Human Barracks" ), BuildData( 200, humanBarracksResourceData ) )
peasant.m_buildData:pushBuildData( QString( "Great Hall" ), BuildData( 400, greatHallResourceData ) )

StaticData:regObjectStaticData( QString( "Peasant" ), peasant )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peasant's static data has been loaded."))