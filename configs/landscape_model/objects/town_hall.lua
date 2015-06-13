
-- Town Hall

object = ObjectStaticData()

object.m_healthData = Object()
object.m_healthData:pushIntMember( HealthComponentMaxHealth, 2100 )
object.m_healthData:pushBoolMember( HealthComponentCanBeRepair, true )
--object.m_healthData:pushBoolMethod( HealthComponentIsHealthy, HealthComponentIsHealthyDefault )
--object.m_healthData:pushVoidIntMethod( HealthComponentSetHealth, HealthComponentSetHealthDefault )

object.m_locateData = Object()
object.m_locateData:pushSizeMember( LocateComponentSize, QSize( 4, 4 ) )
object.m_locateData:pushIntMember( LocateComponentPassability, TerrainMapItem.Ground )
object.m_locateData:pushEmplacementMember( LocateComponentEmplacement, Emplacement.Ground )

object.m_selectionData = Object()
object.m_playerData = Object()

object.m_trainData = Object()

peasantResourceData = ResourcesData()
peasantResourceData:pushResource( QString( "Gold" ), 50 )

trainComponentStaticData = TrainComponentStaticData()
trainComponentStaticData:pushTrainData( QString( "Peasant" ), TrainComponentTrainData( 40, peasantResourceData ) )

object.m_trainData:pushTrainStaticDataMember( TrainComponentStaticDataKey, trainComponentStaticData )

object.m_resourceStorageData = Object()

resourceStorageStaticData = PossibleToStoreData()
resourceStorageStaticData:canStore( QString( "Gold" ) )
resourceStorageStaticData:canStore( QString( "Wood" ) )

object.m_resourceStorageData:pushStorageStaticDataMember( ResourceSourceComponentPossibleToStore, resourceStorageStaticData )

StaticData:regObjectStaticData( QString( "Town Hall" ), object )

-- Object creator

function TownHallCreator( gameObject )

	gameObject:getObjectPtrMember( HealthComponentName ):pushIntMember( HealthComponentHealth, 2100 )
	gameObject:getObjectPtrMember( SelectionComponentName ):pushBoolMember( SelectionComponentIsSelected, false )

	gameObject:getObjectPtrMember( LocateComponentName ):pushDirectionMember( LocateComponentDirection, Direction.South )
	gameObject:getObjectPtrMember( LocateComponentName ):pushBoolMember( LocateComponentIsHidden, false )

	gameObject:getObjectPtrMember( TrainComponentName ):pushBoolMember( TrainComponentProgress, TrainComponentProgressData() )

end

StaticData:regObjectCreator( QString( "Town Hall" ), QString( "TownHallCreator" ) )

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Town Hall's static data has been loaded."))