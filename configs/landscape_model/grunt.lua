
-- Grunt

grunt = ObjectStaticData()

grunt.m_healthData = HealthComponentStaticData( 200 )
grunt.m_locateData = LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem.Ground, Emplacement.Ground )
grunt.m_moveData = MoveComponentStaticData( 1000 )
grunt.m_selectionData = SelectionComponentStaticData( true )
grunt.m_attackData = AttackComponentStaticData(  21, 24, 1.0, 500, 1500 )

StaticData:regObjectStaticData( QString( "Grunt" ), grunt )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Grunt's static data has been loaded."))