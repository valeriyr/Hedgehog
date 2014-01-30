
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

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Elven Archer's static data has been loaded."))