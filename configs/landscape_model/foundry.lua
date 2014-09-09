
-- Foundry

object = ObjectStaticData()

object.m_healthData = HealthComponentStaticData( 1300, true )
object.m_locateData = LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem.Ground, Emplacement.Ground )
object.m_selectionData = SelectionComponentStaticData()
object.m_playerData = PlayerComponentStaticData()

gnomishFlyingMachineResourceData = ResourcesData()
gnomishFlyingMachineResourceData:pushResource( QString( "Gold" ), 1300 )
gnomishFlyingMachineResourceData:pushResource( QString( "Wood" ), 1250 )

object.m_trainData = TrainComponentStaticData()
object.m_trainData:pushTrainData( QString( "Gnomish Flying Machine" ), TrainData( 60, gnomishFlyingMachineResourceData ) )

StaticData:regObjectStaticData( QString( "Foundry" ), object )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Foundry's static data has been loaded."))