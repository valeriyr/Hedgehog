
-- Grunt

grunt = ObjectStaticData()

grunt.m_healthData = HealthComponentStaticData( 200, false )
grunt.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
grunt.m_moveData = MoveComponentStaticData( 10 )
grunt.m_selectionData = SelectionComponentStaticData()
grunt.m_attackData = AttackComponentStaticData(  21, 24, 15, 5, 15 )
grunt.m_playerData = PlayerComponentStaticData()

StaticData:regObjectStaticData( QString( "Grunt" ), grunt )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Grunt's static data has been loaded."))