
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

townHallResourceData = ResourcesData()
townHallResourceData:pushResource( QString( "Gold" ), 1200 )
townHallResourceData:pushResource( QString( "Wood" ), 1100 )

peasant.m_buildData = BuildComponentStaticData()
peasant.m_buildData:pushBuildData( QString( "Human Barracks" ), BuildData( 200, humanBarracksResourceData ) )
peasant.m_buildData:pushBuildData( QString( "Town Hall" ), BuildData( 400, townHallResourceData ) )

StaticData:regObjectStaticData( QString( "Peasant" ), peasant )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peasant's static data has been loaded."))