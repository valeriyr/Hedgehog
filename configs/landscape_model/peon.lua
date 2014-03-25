
-- Peon

peon = ObjectStaticData()

peon.m_healthData = HealthComponentStaticData( 50 )
peon.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
peon.m_moveData = MoveComponentStaticData( 900 )
peon.m_selectionData = SelectionComponentStaticData()
peon.m_attackData = AttackComponentStaticData(  4, 6, 1.0, 400, 1500 )

orcBarracksResourceData = ResourcesData()
orcBarracksResourceData:pushResource( QString( "Gold" ), 400 )
orcBarracksResourceData:pushResource( QString( "Wood" ), 200 )

peon.m_buildData = BuildComponentStaticData()
peon.m_buildData:pushBuildData( QString( "Orc Barracks" ), BuildData( 20000, orcBarracksResourceData ) )

StaticData:regObjectStaticData( QString( "Peon" ), peon )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Peon's static data has been loaded."))