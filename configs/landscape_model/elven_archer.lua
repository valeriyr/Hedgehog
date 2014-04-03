
-- Elven Archer

elvenArcher = ObjectStaticData()

elvenArcher.m_healthData = HealthComponentStaticData( 100, false )
elvenArcher.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
elvenArcher.m_moveData = MoveComponentStaticData( 8 )
elvenArcher.m_selectionData = SelectionComponentStaticData()
elvenArcher.m_attackData = AttackComponentStaticData(  14, 17, 40, 5, 15 )
elvenArcher.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Elven Archer" ), elvenArcher )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Elven Archer's static data has been loaded."))