
-- Peon

peon = ObjectStaticData()

peon.m_healthData = HealthComponentStaticData( 50, false )
peon.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
peon.m_moveData = MoveComponentStaticData( 9 )
peon.m_selectionData = SelectionComponentStaticData()
peon.m_attackData = AttackComponentStaticData( 4, 6, 15, 4, 15 )
peon.m_repairData = RepairComponentStaticData( 1, 30 )
peon.m_playerData = PlayerComponentStaticData()

peon.m_resourceHolderData = ResourceHolderComponentStaticData()
peon.m_resourceHolderData:hold( QString( "Gold" ), 10 )
peon.m_resourceHolderData:hold( QString( "Wood" ), 20 )

orcBarracksResourceData = ResourcesData()
orcBarracksResourceData:pushResource( QString( "Gold" ), 400 )
orcBarracksResourceData:pushResource( QString( "Wood" ), 200 )

greatHallResourceData = ResourcesData()
greatHallResourceData:pushResource( QString( "Gold" ), 1400 )
greatHallResourceData:pushResource( QString( "Wood" ), 1200 )

peon.m_buildData = BuildComponentStaticData()
peon.m_buildData:pushBuildData( QString( "Orc Barracks" ), BuildData( 200, orcBarracksResourceData ) )
peon.m_buildData:pushBuildData( QString( "Great Hall" ), BuildData( 400, greatHallResourceData ) )

StaticData:regObjectStaticData( QString( "Peon" ), peon )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peon's static data has been loaded."))