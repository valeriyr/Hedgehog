
-- Dragon

dragon = ObjectStaticData()

dragon.m_healthData = HealthComponentStaticData( 800 )
dragon.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), AnyTerrain, Emplacement.Air )
dragon.m_moveData = MoveComponentStaticData( 1300 )
dragon.m_selectionData = SelectionComponentStaticData( true )
dragon.m_attackData = AttackComponentStaticData(  56, 64, 3.0, 400, 1500 )

StaticData:regObjectStaticData( QString( "Dragon" ), dragon )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Dragon's static data has been loaded."))