
-- Dragon

dragon = ObjectStaticData()

dragon.m_healthData = HealthComponentStaticData( 800, false )
dragon.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), AnyTerrain, Emplacement.Air )
dragon.m_moveData = MoveComponentStaticData( 13 )
dragon.m_selectionData = SelectionComponentStaticData()
dragon.m_attackData = AttackComponentStaticData(  56, 64, 30, 4, 15 )

StaticData:regObjectStaticData( QString( "Dragon" ), dragon )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Dragon's static data has been loaded."))