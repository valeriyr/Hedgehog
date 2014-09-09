
-- Gold Mine

object = ObjectStaticData()

object.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_selectionData = SelectionComponentStaticData()
object.m_resourceSourceData = ResourceSourceComponentStaticData( QString( "Gold" ) )

StaticData:regObjectStaticData( QString( "Gold Mine" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Gold Mine's static data has been loaded."))